/* monster manipulation function definitions */

#include "monster.h"

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

monster weak_mon[1];
monster mid_mon[1];
monster strong_mon[1];
monster unique_mon[1];

/* linked list stuff */

/*
 * inserts a monster into a linked list, 
 * remember to create the list by declaring
 * the starting pointer to NULL, and to set
 * the starting pointer to the return value of
 * insert_mon();
 */
monster *insert_mon(monster *mlist_ptr, monster *mon_ptr) {

	/* insert new node at start of list */
	mon_ptr->next_mon = mlist_ptr;
	mlist_ptr = mon_ptr;

	return mlist_ptr;
}

/* returns 1 is memory is freed, 0 otherwise */
int delete_mon(monster *mlist_ptr, int mon_num) {
	monster *prev_mon_ptr, *current_mon_ptr, *temp_mon_ptr;

	if (mon_num == mlist_ptr->unum) {
		temp_mon_ptr = mlist_ptr;
		mlist_ptr = mlist_ptr->next_mon;
		free(temp_mon_ptr);
		return 1;
	} else {
		prev_mon_ptr = mlist_ptr;
		current_mon_ptr = mlist_ptr->next_mon;
		
		while (current_mon_ptr != NULL && current_mon_ptr->unum != mon_num) {
			prev_mon_ptr = current_mon_ptr;
			current_mon_ptr = current_mon_ptr->next_mon;
		}

		if (current_mon_ptr != NULL) {
			temp_mon_ptr = current_mon_ptr;
			prev_mon_ptr->next_mon = current_mon_ptr->next_mon;
			free(temp_mon_ptr);
			return 1;
		}
	}
	return 0;
}

void gen_level_mon(int depth, int type) {
}

void init_monsters() {
	monster mon;

	mon.name = "fastrat";
	mon.unum = 0;
	mon.life = 20;
	mon.conc = 0;
	mon.speed = 70;
	mon.arm1 = 2;
	mon.arm2 = 1;
	weak_mon[0] = mon;

/*  mon.name = "";
	mon.unum = ;
	mon.life = ;
	mon.conc = ;
	mon.speed = ;
	mon.arm1 = ;
	mon.arm2 = ;
	weak_mon[] = mon;
*/
}

int monster_present(monster *mlist_ptr, int x, int y) {
	monster *prev_mon_ptr, *current_mon_ptr;

	if (mlist_ptr == NULL) {
		return -1;
	}
	if (x == mlist_ptr->xloc && y == mlist_ptr->yloc) {
		return mlist_ptr->unum;
	} else {
		prev_mon_ptr = mlist_ptr;
		current_mon_ptr = mlist_ptr->next_mon;
		
		while (current_mon_ptr != NULL && current_mon_ptr->xloc != x && current_mon_ptr->yloc != y) {
			prev_mon_ptr = current_mon_ptr;
			current_mon_ptr = current_mon_ptr->next_mon;
		}
		if (current_mon_ptr != NULL) {
			return current_mon_ptr->unum;
		}
	}
	return -1;
}
