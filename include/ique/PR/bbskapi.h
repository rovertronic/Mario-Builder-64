#ifndef __BB_SK_API_HDR__
#define __BB_SK_API_HDR__


/*
 * To add an sk api function:
 *   1) add SK_API_CALL_ define
 *   2) add function prototype in this header
 *   3) implement function in lib/SK/skapi.c
 *   4) add the function to the array skapi_call_table (lib/SK/skapi.c)
 *   5) add entry stub to libultra/bb/sk/skapi.s.
 */

/*
 * Function call mapping numbers, must be in order 0..end
 */

#define SK_API_CALL_GET_ID             0
#define SK_API_CALL_LAUNCH_SETUP       1
#define SK_API_CALL_LAUNCH             2
#define SK_API_CALL_LIST_VALID         3
#define SK_API_CALL_RECRYPT_BEGIN      4
#define SK_API_CALL_RECRYPT_DATA       5
#define SK_API_CALL_RECRYPT_STATE      6
#define SK_API_CALL_RECRYPT_END        7
#define SK_API_CALL_SIGN_HASH          8
#define SK_API_CALL_VERIFY_HASH        9
#define SK_API_CALL_GET_CONSUMPTION    10
#define SK_API_CALL_ADVANCE_TICKET_WINDOW      11
#define SK_API_CALL_SET_LIMIT         12
#define SK_API_CALL_EXIT              13
#define SK_API_CALL_KEEP_ALIVE        14

/*
 * the calls below are for test purpose, not for default or 
 * production build 
 */

#define SK_API_CALL_GET_RAND          15
#define SK_API_CALL_DUMP_VIRAGE       16
#define SK_API_CALL_TEST2             17
#define SK_API_CALL_TEST3             18
#define SK_API_CALL_RESET_WINDOW      19
#define SK_API_CALL_VALIDATE_RLS      20



/* sk api error and return codes. Negative implies failure. */
#define SK_API_SUCCESS                   0
#define SK_API_RECRYPT_NOT_REQUIRED      1
#define SK_API_RECRYPT_COMPLETE          2
#define SK_API_RECRYPT_INCOMPLETE        3
#define SK_API_RECRYPT_NEW               4

#define SK_API_FAIL                     -1
#define SK_API_INVALID_TSRL             -2
#define SK_API_INVALID_CARL             -3
#define SK_API_INVALID_CPRL             -4
#define SK_API_INVALID_CRL              -5
#define SK_API_INVALID_CERT             -6
#define SK_API_INVALID_CONT_HASH        -7
#define SK_API_SIGNER_MISMATCH          -8
#define SK_API_REVOKED_SERVER           -9
#define SK_API_REVOKED_CONTENT          -10
#define SK_API_NO_ENTRY_FOUND           -11

#define SK_IDENTITY            (0x06091968)
#define API_IDENTITY           (0x00000001)

#define SK_RECRYPT_KEYLIST_SIZE (16*1024)

/*
 * Function call declarations.
 *  NOTE: max number of args is 4, and they must fit into a0-a3.  
 */

#if defined(_LANGUAGE_C)

#include <PR/bbticket.h>
#include <PR/bbcert.h>
#include <PR/bbcrl.h>
#include <PR/bbvirage.h>

typedef struct {
    BbCrlHead *head;
    BbServerSuffix *list; /* the actual names of revoked SNs */
    
    /* each pointer points to a cert object */
    BbCertBase *certChain[BB_CERT_CHAIN_MAXLEN];
} BbCrlBundle;

typedef struct {
    BbTicket *ticket;
    BbCertBase *ticketChain[BB_CERT_CHAIN_MAXLEN];
    BbCertBase *cmdChain[BB_CERT_CHAIN_MAXLEN];
} BbTicketBundle;

typedef struct {
    BbCrlBundle tsrl;  /* ticket server revocation list */
    BbCrlBundle carl;  /* certificate authority revocation list */
    BbCrlBundle cprl;  /* content publishing server revocation list */
} BbAppLaunchCrls;
    
    
/*
 * The actual sk api function declarations. All functions
 * return SK_API_ return codes defined above. Any return
 * value < 0 is failure.
 */


/* get the bbid */
int skGetId(BbId *id);

/* setup app launch. does not transfer data.
 */
int skLaunchSetup(BbTicketBundle *ticket,
                  BbAppLaunchCrls *crls,
                  void *pKeyList);

/* setyp app rights and xfer control to app at addr. */
int skLaunch(u32 addr);

/* primes sk for ensuing skRecrypt*() calls.
 * ticket and crls are as in skLaunchSetup().
 * pKeyList will obtain list to be stored.
 * Maximum key list length is 16KB.
 */
int skRecryptListValid(void *pKeyList);

int skRecryptBegin(BbTicketBundle *ticket,
                   BbAppLaunchCrls *crls,
                   void *pKeyList);

int skRecryptData(u8 *data, u32 size);

/* when recovering from aborted recryption attempt, this call must
 * be used to feed the already recrypted data before calling
 * skRecryptData to finish.
 */
int skRecryptComputeState(u8 *data, u32 size);

/* end recyrption and determine success.
 * pKeyList will obtain list to be stored.
 * Maximum key list length is 16KB.
 */
int skRecryptEnd(void *pKeyList);

/*sign hash: operates on SHA-1 hash only, add on an optional identity */
int skSignHash(BbShaHash hash, BbEccSig sign);

/*verify hash: operates on SHA-1 hash only, use an optional identity */
int skVerifyHash(BbShaHash hash, BbGenericSig *sign, BbCertBase *certChain[],
                 BbAppLaunchCrls *crls);


extern int skGetConsumption(u16* tidWindow, u16 cc[BB_MAX_CC]);
extern int skAdvanceTicketWindow(void);
extern int skSetLimit(u16 limit, u16 code);
extern int skExit(void);
extern int skKeepAlive(void);

#ifdef SK_DEVELOP
/* test calls for developement, not for production */
int skGetRandomKeyData(u8 *data, int size); /* max size = 16 bytes */
int skDumpVirage(u8 *virage2data);
int skTest2(int a,int b);
int skTest3(int a,int b);
int skResetWindow(void);
int skValidateRls(BbCrlBundle *carl, BbCrlBundle *cprl, 
		  BbCrlBundle *tsrl, u32 *versions);

#endif

#endif /* _LANGUAGE_C */

#endif


