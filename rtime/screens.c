
#include "screens.h"
#include "character.h"
#include "engine.h"

/* title screen */
void title_screen() {
	char c = '\0';

	write_string(4, 36, "The", L_BLUE);
	write_string(4, 40, "Ship", BLUE);

	write_string(6, 27, "Press  Space  to continue", RED);
	write_char(6, 33, '[', BLUE);
	write_char(6, 39, ']', BLUE);

	while (c != ' ') {
		c = getch();   
	}
}

/* character choice menu */
int world_choice() {
	int i;
	char c = '\0';

	write_string(2, 2, "Choose your homeworld:", CYAN);
	
	write_char(4, 5, 'E', CYAN);
	write_string(4, 7, "arth (1.00G)", BLUE);
	write_char(5, 5, 'N', CYAN);
	write_string(5, 7, "ew Beijing (0.87G)", BLUE);
	write_char(6, 5, 'S', CYAN);
	write_string(6, 7, "parta (1.31G)", BLUE);

	for (i=4; i<7; i++) {
		write_char(i, 4, '[', RED);
		write_char(i, 6, ']', RED);
	}

	for (;;) {
		c = getch();

		if (c == 'e' || c == 'n' || c == 's') {
			break;
		}
		if (c == 'e' || c == 'N' || c == 'S') {
			break;
		}
	}
	
	if (c == 'e' || c == 'E') {
		return EAR;
	}
	if (c == 'n' || c == 'N') {
		return NEW;
	}
	if (c == 's' || c == 'S') {
		return SPA;
	}
	return -1;
}

/* regiment choice menu */
int regiment_choice() {
	int i;
	char c = '\0';

	write_string(2, 2, "Choose your regiment:", CYAN);
	
	write_char(4, 5, 'C', CYAN);
	write_string(4, 7, "ommando", BLUE);
	write_char(5, 5, 'M', CYAN);
	write_string(5, 7, "edic", BLUE);
	write_char(6, 5, 'S', CYAN);
	write_string(6, 7, "apper", BLUE);
	write_string(7, 4, "Sc ", BLUE);
	write_char(7, 7, 'o', CYAN);
	write_string(7, 9, "ut", BLUE);
	write_char(8, 5, 'T', CYAN);
	write_string(8, 7, "echnician", BLUE);
	write_char(9, 5, 'H', CYAN);
	write_string(9, 7, "igh Command", BLUE);
	write_char(10, 5, 'E', CYAN);
	write_string(10, 7, "ngineer", BLUE);

	for (i=4; i<7; i++) {
		write_char(i, 4, '[', RED);
		write_char(i, 6, ']', RED);
	}
	write_char(7, 6, '[', RED);
	write_char(7, 8, ']', RED);
	for (i=8; i<11; i++) {
		write_char(i, 4, '[', RED);
		write_char(i, 6, ']', RED);
	}

	for (;;) {
		c = getch();

		if (c == 'C' || c == 'c') {
			return COM;
		}
		if (c == 'M' || c == 'm') {
			return MED;
		}
		if (c == 'S' || c == 's') {
			return SAP;
		}
		if (c == 'O' || c == 'o') {
			return SCO;
		}
		if (c == 'T' || c == 't') {
			return TEC;
		}
		if (c == 'H' || c == 'h') {
			return HIG;
		}
		if (c == 'E' || c == 'e') {
			return ENG;
		}
	}
}

/* create main game screen */
void main_screen() {

	/* Stuff that doesn't ever change */
	
	/* Primary stats  */
	write_string(3, 72, "Str:", L_GREY);
	write_string(5, 72, "Cdn:", L_GREY);
	write_string(7, 72, "Int:", L_GREY);
	write_string(9, 72, "Con:", L_GREY);
	write_string(11, 72, "Vis:", L_GREY);
	write_string(13, 72, "Cun:", L_GREY);
	write_string(15, 72, "Cha:", L_GREY);

	/* bottom status line */
	write_string(24, 24, "L:   /", L_GREY);
	write_string(24, 34, "C:   /", L_GREY);
	write_string(24, 44, "Spd:", L_GREY);
	write_string(24, 53, "Dge:", L_GREY);
	write_string(24, 60, "A:  /", L_GREY);

	/* top status line */
	write_string(23, 24, "SRW:", L_GREY);
	write_string(23, 53, "LRW:", L_GREY);

	/* print stuff that changes */
	print_stats();   print_2stats();	
	print_weapons(); print_name();
	print_status();
	print_map();
	print_pc();
}

/* print a message to the 2-line message bar at top of screen */
void print_msg(char *msg) {

	/* blank message display */
	write_string(0, 0, "                                   "
				       "                                   "
				       "         ", L_GREY);
	write_string(1, 0, "                                   "
				       "                                   "
				       "         ", L_GREY);

	/* write new message */
	write_string(0, 0, msg, L_GREY);
}

