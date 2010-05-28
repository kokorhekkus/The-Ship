#ifndef RT_ENGINE
#define RT_ENGINE 1

/* color defines */
#define RED     0
#define GREEN   1
#define CYAN    2
#define L_GREY  3
#define BROWN   4
#define BLUE    5
#define MAGENTA 6
#define BLACK   7
#define ORANGE  8
#define L_GREEN 9
#define L_CYAN  10
#define WHITE   11
#define YELLOW  12
#define L_BLUE  13
#define PINK    14
#define D_GREY  15

void init_for_draw(void);

void finish(int);

void write_char(int x, int y, char c, int color);

void write_string(int x, int y, char *s, int color);

void write_line(int x, int y, int type, int length, char c, int color);

void save_screen(char *filepath);

void restore_screen(char *filepath);

void vis_cursor(int visibility);

void set_term_color(int color);

void error_exit(char *msg);

#endif
