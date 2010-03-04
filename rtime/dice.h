
#ifndef RT_DICE
#define RT_DICE 1

int roll_dice(int num_dice, int num_sides, int mod);

int num_inrange(int lowest, int highest);

int percent_chance(int percent);

unsigned int rtrand( void ); /* returns a random 32-bit integer */ 

void rtrand_seed( unsigned int, unsigned int ); /* seed the generator */

#endif
