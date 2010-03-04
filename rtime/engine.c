
/* 
 * Engine function definitions 
 * -these are the platform-dependent functions
 */

#include "engine.h"

#include <ncurses.h>
#include <string.h>
#include <signal.h>
#include <time.h>

/* 
 * initialise ncurses and colors, for drawing the game screen 
 * -includes signal processing/RNG seeding
 */
void init_for_draw(void) {

	srandom(time(NULL));      /* init random seed */
	signal(SIGINT, finish); /* init for finish() */

	/* check for and make the neccesary files and folders */

	/* ncurses init stuff */
	initscr(); 
	/*** CHECK FOR STDSCR !< 80x25 (int LINES,COLS) ***/
	cbreak();  
	nonl();
	noecho();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);

	if (has_colors()) {
		start_color();
		
		/* Set up 8 colors (16 with BOLDing) */
		init_pair(1, COLOR_RED,     COLOR_BLACK);
		init_pair(2, COLOR_GREEN,   COLOR_BLACK);
		init_pair(3, COLOR_CYAN,    COLOR_BLACK);
		init_pair(4, COLOR_WHITE,   COLOR_BLACK);
		init_pair(5, COLOR_YELLOW,  COLOR_BLACK);
		init_pair(6, COLOR_BLUE,    COLOR_BLACK);
		init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(8, COLOR_BLACK,   COLOR_BLACK);
	}
}

/* write a character, 'c', to the co-ords (x,y) with colour 'color' */
void write_char(int x, int y, char c, int color) {
	chtype ch = c;
 
	set_term_color(color);
	mvaddch(x,y,ch);
	refresh();
}

/* write a string, 's', to the co-ords (x,y) with colour 'color' */
void write_string(int x, int y, char *s, int color) {
	int i, s_len;
	chtype ch;

	set_term_color(color);
	s_len = strlen(s);

	for (i=0; i < s_len; i++) {
		ch = s[i];
		mvaddch(x,y+i,ch);
	}	
	refresh();
}

/*
 * write a line of color 'color' and length 'length' starting at (x,y) 
 * 'type' is 1 - horizontal, 2 - vertical
 */
void write_line(int x, int y, int type, int length, char c, int color) {
	int i;
	chtype ch;

	set_term_color(color);

	for (i=0;i<length;i++) {
		if (type == 1) {
			ch = c;
			mvaddch(x,y+i,ch);
		}
		if (type == 2) {
			ch = c;
			mvaddch(x+i,y,ch);
		}
	}
	refresh();
}


/* save current screen to a file */
void save_screen(char *filepath) {
	FILE *tmpscrdat = fopen(filepath, "w+");

	if ((putwin(stdscr, tmpscrdat)) == ERR) {
		error_exit("Can't save temporary data to disk!");
	}
}

/* restore screen from a file */
void restore_screen(char *filepath) {
	FILE *tmpscrdat = fopen(filepath, "r");

	if (tmpscrdat == NULL) {
		error_exit("Can't find data file to load!");
	}
	stdscr = getwin(tmpscrdat);
	refresh();
}

/* finish up, get rid of 'stdscr' */
void finish(int sig) {
	endwin();
	printf("\nTerminated with signal %i\n\n", sig);
	printf("The Ship Version 0.1\n");
	printf("(C) Copyright 2002 Karim Rashad\n");
	printf("All Rights Reserved\n\n");
	exit(0);
}

/* makes cursor appear or disappear: 1 - visible, 0 - not visible */
void vis_cursor(int visibility) {
	int v;

	if (visibility) {
		v = curs_set(1);
	} else {
		v = curs_set(0);
	}
}

/* set the video color attribute of a terminal once */
void set_term_color(int color) {

	if (color == RED) {
		attrset(COLOR_PAIR(1));
	}
	if (color == GREEN) {
		attrset(COLOR_PAIR(2));
	}
	if (color == CYAN) {
		attrset(COLOR_PAIR(3));
	}
	if (color == L_GREY) {
		attrset(COLOR_PAIR(4));
	}
	if (color == BROWN) {
		attrset(COLOR_PAIR(5));
	}
	if (color == BLUE) {
		attrset(COLOR_PAIR(6));
	}
	if (color == MAGENTA) {
		attrset(COLOR_PAIR(7));
	}
	if (color == BLACK) {
		attrset(COLOR_PAIR(8));
	}
	if (color == ORANGE) {
		attrset(COLOR_PAIR(1) | A_BOLD);
	}
	if (color == L_GREEN) {
		attrset(COLOR_PAIR(2) | A_BOLD);
	}
	if (color == L_CYAN) {
		attrset(COLOR_PAIR(3) | A_BOLD);
	}
	if (color == WHITE) {
		attrset(COLOR_PAIR(4) | A_BOLD);
	}
	if (color == YELLOW) {
		attrset(COLOR_PAIR(5) | A_BOLD);
	}
	if (color == L_BLUE) {
		attrset(COLOR_PAIR(6) | A_BOLD);
	}
	if (color == PINK) {
		attrset(COLOR_PAIR(7) | A_BOLD);
	}
	if (color == D_GREY) {
		attrset(COLOR_PAIR(8) | A_BOLD);
	}
}

/* exit program and print an error message */
void error_exit(char *msg) {
	endwin();
	printf("\n\n*******************************************************************************\n");
	printf("* RT_ERROR: %s\n", msg);
	printf("*******************************************************************************\n");
	exit(0);
}
