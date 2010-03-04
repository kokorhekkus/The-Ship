 
#include "map.h"
#include "engine.h"
#include "object.h"

#include <ncurses.h>
#include <assert.h>

mapchar mapmap[8];

object *lev1 = NULL;

/* an 80x25 screen */
mapchar curr_level[25][80] = {};

extern int location[];

/* set up the character mapping */
void set_mapdrawing_chars() {
	mapchar mc;

	mc.unum = 0;
	mc.symbol = '\0';
	mc.color = WHITE;
	mapmap[BLANK] = mc;

	mc.unum = 1;
	mc.symbol = '#';
	mc.color = D_GREY;
	mapmap[WALL] = mc;

	mc.unum = 2;
	mc.symbol = '.';
	mc.color = L_GREY;
	mapmap[FLR] = mc;

	mc.unum = 3;
	mc.symbol = '<';
	mc.color = WHITE;
	mapmap[UPSTR] = mc;

	mc.unum = 4;
	mc.symbol = '>';
	mc.color = WHITE;
	mapmap[DNSTR] = mc;

	mc.unum = 5;
	mc.symbol = '+';
	mc.color = WHITE;
	mapmap[CDOOR] = mc;

	mc.unum = 6;
	mc.symbol = '|';
	mc.color = WHITE;
	mapmap[ODOOR] = mc;
}

/*
 * write a line of color 'color' and length 'length' starting at (x,y) 
 * 'type' is 1 - horizontal, 2 - vertical
 * -writes to the current level screen array
 */
void write_mapline(int x, int y, int type, int length, mapchar feat) {
	int i;

	for (i=0;i<length;i++) {
		if (type == 1) {
			curr_level[x][y+i] = feat;
		}
		if (type == 2) {
			curr_level[x+i][y] = feat;
		}
	}
}

int gen_level(int depth, int type) {

	gen_level_map(depth, type);
	gen_level_obj(depth, type);
	/* gen_level_mon(depth, type); */
	return 1;
}

/* 'blank' map array */
void init_screen_array() {

	int x,y;

	for (x = 0; x < 80; x++) {
		for (y = 0; y < 25; y++) {
			curr_level[y][x] = mapmap[BLANK];
		}
	}
}

/* generate level map*/
void gen_level_map(int depth, int type) {
	int x, y;
	int x_length, y_length;
	int pc_xloc, pc_yloc;
	int border_present = 0;
	int space_avail = 0;
	int sa_x, sa_y;

	if (type == CORRIDORS) {
		/* fill up level array with 'wall' */
		for (x = DRAW_X_MIN; x < DRAW_X_MAX; x++) {
			for (y = DRAW_Y_MIN; y < DRAW_Y_MAX; y++) {
				curr_level[x][y] = mapmap[WALL];
			}
		}
		
		/* hollow out a rectangular room at a random position. near   */
		/* center of level.                                           */
				
		/* NOTE: THESE ARE THE MAX RANGES TO DRAW FEATURES TO: */
		/*make_straight_path(DRAW_X_MIN+2,DRAW_Y_MIN+1,DRAW_X_MAX-2,DRAW_Y_MAX-2);*/

        /*  -create inital room */
		x = num_inrange(DRAW_X_MIN + 8, DRAW_X_MAX - 8);

		y = num_inrange(DRAW_Y_MIN + 18, DRAW_Y_MAX - 30);
		x_length = num_inrange(4, MAX_ROOM_SIZE); 
		y_length = num_inrange(4, MAX_ROOM_SIZE);
		
		make_room(SQUARE, x, y, x_length, y_length);

		/* set initial PC position and up staircase */
		pc_xloc = x + 1; pc_yloc = y + 1;
		location[0] = pc_xloc;
		location[1] = pc_yloc;
		location[2] = pc_xloc - 1;
		location[3] = pc_yloc - 1;

		curr_level[pc_xloc][pc_yloc] = mapmap[UPSTR];

		/* determine where to draw the next feature */
		/* -find junction of wall/non-wall          */
		while(border_present != 1) {

			x = num_inrange(DRAW_X_MIN+2,DRAW_X_MAX-2);
			y = num_inrange(DRAW_Y_MIN+1,DRAW_Y_MAX-2);
			
			if ((curr_level[x][y+1].unum == mapmap[FLR].unum) || 
				(curr_level[x][y-1].unum == mapmap[FLR].unum) || 
				(curr_level[x+1][y].unum == mapmap[FLR].unum) || 
				(curr_level[x-1][y].unum == mapmap[FLR].unum)) {
				
				if (curr_level[x][y].unum == mapmap[WALL].unum) {
					border_present = 1;
				} else {
					border_present = 0;
				}
			} else {
				border_present = 0;
			}
		}
		
		/* x,y is junction point */
		lev1 = add_obj(lev1, 1, SRW, 1, x, y);

		/* -add a room or a corridor */
		
		

		/* sa_x = x;
		sa_y = y;
		space_avail++;
		if (curr_level[x][y+1].unum == mapmap[FLR].unum) {

			while (curr_level[sa_x][sa_y].unum == mapmap[WALL].unum) { 
				sa_y--; 
				space_avail++;
			}
			
			if (space_avail > 1) {
				x_length = num_inrange(1,space_avail);
				make_straight_path(x,y,x,y-x_length);
			}
		}
		if (curr_level[x][y-1].unum == mapmap[FLR].unum) {
			
			while (curr_level[sa_x][sa_y].unum == mapmap[WALL].unum) { 
				sa_y++; 
				space_avail++;
			}

			if (space_avail > 1) {
				x_length = num_inrange(1,space_avail);
				make_straight_path(x,y,x,y+x_length);
			}
		}
		if (curr_level[x+1][y].unum == mapmap[FLR].unum) {
			
			while (curr_level[sa_x][sa_y].unum == mapmap[WALL].unum) { 
				sa_x--; 
			space_avail++;
			}

			if (space_avail > 1) {
				y_length = num_inrange(1,space_avail);
				make_straight_path(x,y,x-y_length,y);
			}
		}
		if (curr_level[x-1][y].unum == mapmap[FLR].unum) {

			while (curr_level[sa_x][sa_y].unum == mapmap[WALL].unum) { 
				sa_x++; 
				space_avail++;
			}

			if (space_avail > 1) {
				y_length = num_inrange(1,space_avail);
				make_straight_path(x,y,x+y_length,y);
			}
			}*/
	}
}

void make_room(int type, int x_start, int y_start, int x_length, int y_length) {
	int r;
	if (type == SQUARE) {
		/* top left hand corner at [x_start. y_start */
		/* (write floorspace within the 'solid' level) */
		for (r = 0; r < y_length; r++) {
			write_mapline(x_start + r, y_start, 1, x_length, mapmap[FLR]);
		}
	}
}

void make_straight_path(int x_start, int y_start, int x_end, int y_end) {
	int x = x_start;
	int y = y_start;
	
	curr_level[x][y] = mapmap[FLR];

	if (x <= x_end) {
		while (x != x_end) {
			x++;
			curr_level[x][y] = mapmap[FLR];
		}
	} else {
		while (x != x_end) {
			x--;
			curr_level[x][y] = mapmap[FLR];
		}
	}

	if (y <= y_end) {
		while (y != y_end) {
			y++;
			curr_level[x][y] = mapmap[FLR];
		}
	} else {
		while (y != y_end) {
			y--;
			curr_level[x][y] = mapmap[FLR];
		}
	}
}

/*
void make_jagged_path(int x_start, int y_start, int x_end, int y_end) {
	int x = x_start;
	int y = y_start;
	int c;
	int last_dir = -1;
	
	curr_level[x][y] = mapmap[FLR];
	
	for (c = 0; c < 100; c++) {
		if (percent_chance(50)) {
			if (percent_chance(50)) {
				if (y != DRAW_Y_MAX || y != DRAW_Y_MIN) {
					if (last_dir != 0) {
						y += 1;
						last_dir = 0;
					}
				}
			} else {
				if (y != DRAW_Y_MAX || y != DRAW_Y_MIN) {
					if (last_dir != 1) {
						y -=  1;
						last_dir = 1;
					}
				}
			}
		} else {
			if (percent_chance(50)) {
				if (x != DRAW_X_MAX || x != DRAW_X_MIN) {
					if (last_dir != 2) {
						x += 1;
						last_dir = 2;
					}
				}
			} else {
				if (x != DRAW_X_MAX || x != DRAW_X_MIN) {
					if (last_dir != 3) {
						x -= 1;
						last_dir = 3;
					}
				}
			}
		}
		curr_level[x][y] = mapmap[FLR];
	}
}
*/

void print_map() {

	draw_lfeats();
	draw_lobjects();
}

/* save a level to a temporary file */
void save_level() {

}

/* restore a level from a file to the screen */
void restore_level() {

}

/* draw the level objects to the screen */
void draw_lobjects() {

	int obj_num = 0;
	int c;
	int numo = object_number(lev1);
	char num_msg[20];

	sprintf(num_msg, "Number: %i", numo);

	if (lev1 != NULL) {
		for (c=0; obj_num < object_number(lev1); obj_num++) {
			int xloc = get_xloc(lev1, obj_num); int yloc = get_yloc(lev1, obj_num);
			char sym = get_look(lev1, obj_num); int col = get_color(lev1, obj_num);
			
			write_char(xloc,yloc,sym,col);
		}
	}
}

/* open a door */
int open_door() {

	int doorxloc, dooryloc;
	char loc_char;

	print_msg("Which direction?");
	
	for(;;) {
		char c = getch();
		int no_dir = 1;

		if (c == 'h') {
			doorxloc = location[0];
			dooryloc = location[1] - 1;
			no_dir = 0;
		}
		if (c == 'j') {
			doorxloc = location[0] + 1;
			dooryloc = location[1];
			no_dir = 0;
		}
		if (c == 'k') {
			doorxloc = location[0] - 1;
			dooryloc = location[1];
			no_dir = 0;
		}
		if (c == 'l') {
			doorxloc = location[0];
			dooryloc = location[1] + 1;
			no_dir = 0;
		}
		if (c == 'y') {
			doorxloc = location[0] - 1;
			dooryloc = location[1] - 1;
			no_dir = 0;
		}
		if (c == 'u') {
			doorxloc = location[0] - 1;
			dooryloc = location[1] + 1;
			no_dir = 0;
		}
		if (c == 'b') {
			doorxloc = location[0] + 1;
			dooryloc = location[1] - 1;
			no_dir = 0;
		}
		if (c == 'n') {
			doorxloc = location[0] + 1;
			dooryloc = location[1] + 1;
			no_dir = 0;
		} 
		
		if (no_dir == 1) {
			print_msg("Interesting direction...");
			return -1;
		}
	
		loc_char = (char)(mvwinch(stdscr, doorxloc, dooryloc));
		
		if (loc_char == '+') {
			curr_level[doorxloc][dooryloc] = mapmap[ODOOR];
			print_map();
			print_pc();
			print_msg("The door slides open.");
			return 1;
		} else {
			print_msg("Where?");
			return 0;
		}
	}
	
}

/* draw the level from the curr_level array */
void draw_lfeats() {
	int x,y;
	for (x = 0; x < 25; x++) {
		for (y = 0; y < 80; y++) {
			if (curr_level[x][y].unum != mapmap[BLANK].unum) {
				write_char(x, y, curr_level[x][y].symbol, curr_level[x][y].color);
			}	
		}
	}
}
