
/**
 * Behavior for bhvActivatedBackAndForthPlatform.
 * There are only 2 of these in the game; the BitFS gray elevator
 * and the BitS arrow platform.
 * Note: The filename is abbreviated to avoid compiler seg fault on long paths
 */

/**
 * Table of activated back-and-forth platform collision models.
 * The second entry is unused. It corresponds to the mesh platform
 * at the beginning of BitFS. In the game, it's a bhvPlatformOnTrack,
 * which allows for more complex movement; its path is mostly a straight line
 * except for where it dips into the lava. It seems the programmers
 * had it as a bhvActivatedBackAndForthPlatform initially, which moves
 * in a straight line, and wanted it to dip into the lava to make Mario have to
 * move off of it. To do this, they changed it to a bhvPlatformOnTrack, but
 * forgot to remove its entry in this table.
 */

/**
 * Activated back-and-forth platform initialization function.
 */
//! TODO: Param names
void bhv_activated_back_and_forth_platform_init(void) {
}

/**
 * Activated back-and-forth platform update function.
 */
void bhv_activated_back_and_forth_platform_update(void) {

}
