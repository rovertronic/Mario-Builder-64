#ifndef MEM_ERROR_SCREEN_H
#define MEM_ERROR_SCREEN_H

extern u8 gNotEnoughMemory;
void thread5_mem_error_message_loop(UNUSED void *arg);
u8 does_pool_end_lie_out_of_bounds(void *end);

#endif
