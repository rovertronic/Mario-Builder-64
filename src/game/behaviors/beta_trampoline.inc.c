
/**
 * Behavior for bhvBetaTrampolineTop and bhvBetaTrampolineSpring.
 * This was a trampoline that was never finished. The model and collision
 * are nearly finished, but the code was abandoned very early on
 * in its development. The trampoline consists of 3 objects: the top,
 * the spring, and the base. The base is a static object with no behavior.
 */

/**
 * Update function for bhvBetaTrampolineSpring.
 * The spring continuously updates to be 75 units below the top.
 * It then uses its displacement from its original position
 * (i.e. how much the trampoline has compressed) to calculate its
 * vertical scale factor, so that it compresses visually along with
 * the trampoline. The devs were on the right track with the math,
 * but it is incomplete.
 */
void bhv_beta_trampoline_spring_loop(void) {

}

/**
 * Update function for bhvBetaTrampolineTop.
 * This spawns the other 2 trampoline parts when initialized,
 * and sets a boolean for whether Mario's on or off the trampoline.
 * The trampoline top never actually moves, so the spring will never
 * do anything.
 */
void bhv_beta_trampoline_top_loop(void) {

}
