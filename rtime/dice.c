
#include "dice.h"

#include <stdlib.h>
#include <assert.h>

static unsigned int SEED_X = 521288629;
static unsigned int SEED_Y = 362436069; 

/*
 * Returns a number which is equivalent to rolling a
 * dice like, '3d4+5' where num_dice = 3, num_sides = 4, mod = 5
 */
int roll_dice(int num_dice, int num_sides, int mod) {
	int rnum = 0;
	int i = 0;

	assert(num_dice > 0);
	assert(num_sides > 0);
	assert(mod >= 0);

	for (i; i<num_dice; i++) {		
		int frnum = num_inrange(1,num_sides);
		rnum += frnum;
	}
	return rnum + mod;
}

/* returns a number in the range, lowest >= num <= highest  */
int num_inrange(int lowest, int highest) {
	int rnum;

	assert(lowest < highest);

	rnum = lowest + (int)(random() % (highest + 1));

	return rnum;
}

int percent_chance(int percent) {
	int num = num_inrange(0, 100);

	assert(percent >=0);

	if (num > percent) {
		return 0;
	} else{
		return 1;
	}
}

/* returns a random 32-bit integer */ 
unsigned int rtrand () {
         /* Use any pair of non-equal numbers from this list for "a" and "b"

        18000 18030 18273 18513 18879 19074 19098 19164 19215 
        19584 19599 19950 20088 20508 20544 20664 20814 20970 
        21153 21243 21423 21723 21954 22125 22188 22293 22860 
        22938 22965 22974 23109 23124 23163 23208 23508 23520 
        23553 23658 23865 24114 24219 24660 24699 24864 24948 
        25023 25308 25443 26004 26088 26154 26550 26679 26838 
        27183 27258 27753 27795 27810 27834 27960 28320 28380 
        28689 28710 28794 28854 28959 28980 29013 29379 29889 
        30135 30345 30459 30714 30903 30963 31059 31083 */

        static unsigned int a = 18000, b = 30903;
        SEED_X = a*(SEED_X&65535) + (SEED_X >> 16);
        SEED_Y = b*(SEED_Y&65535) + (SEED_Y >> 16);
        return ((SEED_X<<16) + (SEED_Y&65535)); 
} 

/* seed the generator */
void rtrand_seed( unsigned int seed1, unsigned int seed2 )
{
         if (seed1) SEED_X = seed1; /* use default seeds if parameter is 0*/
         if (seed2) SEED_Y = seed2; 
} 
