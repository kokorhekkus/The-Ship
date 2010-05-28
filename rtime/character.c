
#include "character.h"
#include "engine.h"
#include "object.h"
#include "map.h"

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

/* 
 * -primary stats
 * max. stat : 50
 */
int char_stats[7] = {0};
/* 
 * -secondary stats
 * max stats:
 * S: 100
 * A: 99/99
 * C: 999/999
 * L: 999/999
 * D: 99
 * XL: 50
 */
int sec_stats[12] = {0};
 
char pc_status[23] = {'\0'}; 
char pc_name[23]   = {'\0'}; 

/* pc's location - current_x, current_y, last_x, last_y */
int location[4] = {7,45,6,46};

object *inventory = NULL; /* inventory list */
object equip[7]; 

extern object *lev1;
extern mapchar curr_level[25][80];

/* roll the PCs starting stats; */
void roll_pc(int class, int regiment) {
	int i;
	/* array of how to modify the RNG's initial rolls */
	static int mod_stats[7] = {0};

	if (class == EAR) {
		mod_stats[STR] = -3;
		mod_stats[CUN] = 0;
		mod_stats[INT] = 3;
		mod_stats[CON] = -1;
		mod_stats[VIS] = -1;
		mod_stats[COO] = 0;
		mod_stats[CHA] = 0;
	}
	if (class == NEW) {
		mod_stats[STR] = 3;
		mod_stats[CUN] = 1;
		mod_stats[INT] = -2;
		mod_stats[CON] = 1;
		mod_stats[VIS] = 1;
		mod_stats[COO] = 0;
		mod_stats[CHA] = -2;
	}
	if (class == SPA) {
		mod_stats[STR] = -3;
		mod_stats[CUN] = 1;
		mod_stats[INT] = 3;
		mod_stats[CON] = -1;
		mod_stats[VIS] = -1;
		mod_stats[COO] = 1;
		mod_stats[CHA] = 0;
	}

	for (i=0; i<7; i++) {
		char_stats[i] =  roll_dice(1,14,2);
		char_stats[i] += mod_stats[i];
	}
}

/*
 * change stat 'stat' by 'sincr'
 * 's_or_p' changes secondary or primary stats array
 *  1:  primary, 2: secondary
 * example call : increase_stat(STR, 2)
 *  -increases Strength by 2
 */
void change_stat(int stat, int sincr, int s_or_p) {
	if (s_or_p == 1) {
		char_stats[stat] += sincr;
	} else {
		sec_stats[stat]  += sincr;
	}
}

/* prints the primary stats array to the screen */
void print_stats() {
	write_string(3, 77, (char *)inttostr(char_stats[STR]), WHITE);
    write_string(5, 77, (char *)inttostr(char_stats[COO]), WHITE);
	write_string(7, 77, (char *)inttostr(char_stats[INT]), WHITE);
	write_string(9, 77, (char *)inttostr(char_stats[CON]), WHITE);
	write_string(11, 77, (char *)inttostr(char_stats[VIS]), WHITE);
	write_string(13, 77, (char *)inttostr(char_stats[CUN]), WHITE);
	write_string(15, 77, (char *)inttostr(char_stats[CHA]), WHITE); 
}

void print_2stats() {
	write_string(24, 26, (char *)inttostr(sec_stats[L1]), WHITE);
	write_string(24, 30, (char *)inttostr(sec_stats[L2]), WHITE);
	write_string(24, 36, (char *)inttostr(sec_stats[C1]), WHITE);
	write_string(24, 40, (char *)inttostr(sec_stats[C2]), WHITE);
	write_string(24, 62, (char *)inttostr(sec_stats[A1]), WHITE);
	write_string(24, 65, (char *)inttostr(sec_stats[A2]), WHITE);
	write_string(24, 57, (char *)inttostr(sec_stats[DG]), WHITE);
	write_string(24, 48, (char *)inttostr(sec_stats[SP]), WHITE);
}

void print_name() {
	write_string(23, 0, pc_name, L_GREY);
}

void print_status() {
	write_string(24, 0, pc_status, L_GREY);
}

/* generate initial secondary stats */
void gen_secondary_stats() {

	/* Experience initial */
	sec_stats[XP] = 0;
	sec_stats[XL] = 1;

	/* Life points initial calculation  */
	sec_stats[L1] = sec_stats[L2] = char_stats[CON] + (char_stats[STR] / 4);

	/* Concentration points initial calculation  */	
	sec_stats[C1] = sec_stats[C2] = char_stats[INT] + roll_dice(1,6,0); 
    /*** plus class modifiers ***/

	/* Armour initial Calculation  */	
	sec_stats[A1] = 3;
	sec_stats[A2] = 4;
	
	/* Speed initial calculation  */	
	sec_stats[SP] = char_stats[COO] + (char_stats[CUN] / 4) + 50;

	/* Dodge initial calculation  */	
	sec_stats[DG] = sec_stats[SP] + char_stats[STR] + char_stats[VIS];
}


/* get player's name */
void get_pcname() {
	write_string(4, 8, "Name yourself", CYAN);
	write_char(4, 21, ':', L_BLUE);
	write_char(4, 22, ' ', L_GREY);
 
	echo();
	if (getnstr(pc_name, 23) == ERR) {
		/*** terminate and print overflow (probably) error message ***/
	}
	noecho();
}

/* write pc to present location */
/* also writes last sq. */
void print_pc() {
	mapchar last_loc;
	int lastx, lasty;
	int onum;

	/* present location */
	write_char(location[0], location[1], '@', RED);

	/* last square */
	lastx = location[2];
	lasty = location[3];
	
	/* this is FUCKED */
	onum = object_present(lev1, lastx, lasty);
	if (onum != -1) {
		write_char(location[2], location[3], get_look(lev1, onum), get_color(lev1, onum));
	} else {
		last_loc = curr_level[lastx][lasty];
		write_char(location[2], location[3], last_loc.symbol, last_loc.color);
	}
}

/* 
 * shift location by x,y 
 * -returns code of any obstacles/monster
 * 0 : don't move; wall
 * 1 : OK to move normally; empty square
 * 2 : object on floor
 * 3 : a closed door
 */
int move_pc(int x, int y) {
	int xfloc =  location[0] + x; int yfloc =  location[1] + y;
	/* get symbol at intended location */
	char iloc = (char)(mvwinch(stdscr, xfloc, yfloc));

	/* a wall */
	if (iloc == '#') {
		print_msg("That's a wall.");
		return 0;
	} 

	/* a closed door */
	if (iloc == '+') {
		print_msg("You bump into the door.");
		return 3;
	}

	/* an object */
	if (iloc == '(' || iloc == ')' || iloc == '/' || iloc == '\\' || iloc == '%' || iloc == '$' || iloc == '!' || iloc == '?') {
		char *namebuf; 
		if (lev1 != NULL) {
			char *obj_name = get_oname(lev1, get_unum(lev1, xfloc, yfloc));
			char obj_msg[30] = "You see a ";   
			char *obj_end = ".";
			strcat(obj_msg, obj_name);
			namebuf = (char *)strcat(obj_msg, obj_end);
		} else {
			namebuf = NULL;
		}
		print_msg(namebuf);  
		location[2] = location[0];
		location[3] = location[1];
		location[0] += x;
		location[1] += y;
		return 2;
	} else {
		/* clear message bar on movement */
		print_msg("");
	}

	/* if OK, go ahead and change location */
	location[2] = location[0];
	location[3] = location[1];
	location[0] += x;
	location[1] += y;
	return 1;
}

/* returns unum of item picked up */
int get_from_flr() {
	object *prev_obj_ptr, *current_obj_ptr;
	const char obj_msg[30] = "You pick up the ";

	if (lev1 == NULL) {
		print_msg("There's nothing here.");
		return -1;
	}

	if (lev1->xloc == location[0] && lev1->yloc == location[1]) {
		char *msg;
		int ounum = lev1->unum;
		const char *obj_name = get_oname(lev1, ounum);
		const char *msg_end = ".";
		strcat(obj_msg, obj_name);
	    msg = (char *)strcat(obj_msg, msg_end);
  		print_msg(msg);
	
	    /* remove from floor list, put in inventory list */
		inventory = insert_obj(inventory, lev1);
		lev1 = delete_obj(lev1, lev1->unum);

		return ounum;
	} else {
		prev_obj_ptr = lev1;
		current_obj_ptr = lev1->next_obj;
		while (current_obj_ptr != NULL && (current_obj_ptr->xloc != location[0] || current_obj_ptr->yloc != location[1])) {
			prev_obj_ptr = current_obj_ptr;
			current_obj_ptr = current_obj_ptr->next_obj;
		}
		if (current_obj_ptr != NULL) {
			char *msg;
			int ounum = current_obj_ptr->unum;
			const char *obj_name = get_oname(current_obj_ptr, ounum);
			const char *msg_end = ".";
			strcat(obj_msg, obj_name);
			msg = (char *)strcat(obj_msg, msg_end);
			print_msg(msg);
			
			/* remove from floor list, put in inventory list */
			inventory = insert_obj(inventory, lev1);
			lev1 = delete_obj(lev1, current_obj_ptr->unum);
			
			return ounum;
		}
	} 
	return -1;
}
