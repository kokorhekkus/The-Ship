#ifndef RT_MAP
#define RT_MAP 1

/* holds colors/characters for map-drawing */
typedef struct mapchar {
	int unum;
	char symbol;
	int  color;
} mapchar;

/* defines for map square types (mapchar struct) */
#define BLANK 0
#define WALL  1
#define FLR   2
#define UPSTR 3
#define DNSTR 4
#define CDOOR 5
#define ODOOR 6

/* defines for level types */
#define CORRIDORS 0
#define FUEL_SEA  1
#define FOREST    2
#define CAVERN    3

/* defines for room types */
#define SQUARE 0

/* define the size of the drawable area */
#define DRAW_X_MIN 2
#define DRAW_Y_MIN 2
#define DRAW_X_MAX 23
#define DRAW_Y_MAX 71

/* max room size */
#define MAX_ROOM_SIZE 7

enum Direction {N, NE, E, SE, S, SW, W, NW};

void set_mapdrawing_chars();

void write_mapline(int x, int y, int type, int length, mapchar feat);

int gen_level(int depth, int type);

void save_level();

void restore_level();

void draw_lobjects();

void init_screen_array();

void gen_level_map(int depth, int type);

void make_room(int type, int x_start, int y_start, int x_length, int y_length);

void make_straight_path(int x_start, int y_start, int x_end, int y_end);

/* void make_jagged_path(int x_start, int y_start, int x_end, int y_end); */

void print_map();

/* returns 1 if door is there, 0 otherwise */
int open_door();

/*
 * draw the level features; current level
 * features are held in a global array
 */
void draw_lfeats();

#endif
