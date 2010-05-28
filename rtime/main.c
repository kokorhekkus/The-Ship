#include "engine.h"
#include "object.h"
#include "map.h"
#include "rtutil.h"
#include "log.h"
#include "character.h"

#include <ncurses.h>

int main(int argc, char *argv[]) {
	char *wmsg = "You're inside.";
	int w_choice = 0;
	int r_choice = 0;

	rtlog("Initialising");
	/* init, and enter game loop checking for keyboard input */
	init_for_draw();
	init_objects();
	init_monsters();
	init_log();
	set_mapdrawing_chars();
	init_screen_array();

	rtlog("Going to title screen");
	vis_cursor(0);
	title_screen();
	clear();

	rtlog("Getting name");
	vis_cursor(1);
	get_pcname();
	clear();
	vis_cursor(0);

	rtlog("Getting origin world");
	w_choice = world_choice();
	clear();
	rtlog("Getting regiment choice");
	r_choice = regiment_choice();
	rtlog("Rolling PC stats");
	roll_pc(w_choice, r_choice);
	rtlog("Generating starting inventory");
	gen_sinv(w_choice, r_choice);
	rtlog("Deducing secondary stats");
	gen_secondary_stats();
	clear();

	rtlog("Generating starting level");
	gen_level(1,CORRIDORS);
	main_screen();

	print_msg(wmsg);

	rtlog("Entering main game loop");
	for (;;) {

		/* get keyb input */
		char c = getch();

		/*color test */
		if (c == 'c') {
			save_screen("scrtocol.tdd");
			clear();
			write_line(4,30,1,20,'r',RED);
			write_line(5,30,1,20,'g',GREEN);
			write_line(6,30,1,20,'c',CYAN);
			write_line(7,30,1,20,'g',L_GREY);
			write_line(8,30,1,20,'b',BROWN);
			write_line(9,30,1,20,'b',BLUE);
			write_line(10,30,1,20,'m',MAGENTA);
			write_line(11,30,1,20,'b',BLACK);
			write_line(12,30,1,20,'o',ORANGE);
			write_line(13,30,1,20,'g',L_GREEN);
			write_line(14,30,1,20,'c',L_CYAN);
			write_line(15,30,1,20,'w',WHITE);
			write_line(16,30,1,20,'y',YELLOW);
			write_line(17,30,1,20,'b',L_BLUE);
			write_line(18,30,1,20,'p',PINK);
			write_line(19,30,1,20,'g',D_GREY);
		}
		if (c == 'C') {
			clear();
			restore_screen("scrtocol.tdd");
		}

		/* Rogue-like movement keys & cursor keys*/
		/*** TODO: NUMBERPAD ***/
		if (c == 'h' || c == KEY_LEFT)  {
			int mtype = move_pc(0,-1);
			if (mtype==1 || mtype==2) {
				print_pc();
			}
		}
		if (c == 'j' || c == KEY_DOWN) {
			int mtype = move_pc(1,0);
			if (mtype==1 || mtype==2) {
				print_pc();
			}
		}
		if (c == 'k' || c == KEY_UP) {
			int mtype = move_pc(-1,0);
			if (mtype==1 || mtype==2) {
				print_pc();
			}
		}
		if (c == 'l' || c == KEY_RIGHT) {
			int mtype = move_pc(0,1);
			if (mtype==1 || mtype==2) {
				print_pc();
			}
		}
		if (c == 'y') {
			int mtype = move_pc(-1,-1);
			if (mtype==1 || mtype==2) {
				print_pc();
			}
		}
		if (c == 'u') {
			int mtype = move_pc(-1,1);
			if (mtype==1 || mtype==2) {
				print_pc();
			}
		}
		if (c == 'b') {
			int mtype = move_pc(1,-1);
			if (mtype==1 || mtype==2) {
				print_pc();
			}
		}
		if (c == 'n') {
			int mtype = move_pc(1,1);
			if (mtype==1 || mtype==2) {
				print_pc();
			}
		}

		/* open a door */
		if (c == 'o') { open_door(); }

		/* pick up objects from the floor */
		if (c == ',') { get_from_flr(); }

		/* Inventory screen */
		if (c == 'i') { show_inventory(); }

		/* Quit */
		if (c == 'Q') { break; }
	}
	finish(0);

	return 1;
}
