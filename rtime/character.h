#ifndef RT_CHARACTER
#define RT_CHARACTER 1

/* define primary stats */
#define STR 0
#define CUN 1
#define INT 2
#define CON 3
#define VIS 4
#define COO 5
#define CHA 6

/* define secondary stats and player charateristics */
#define L1 0
#define L2 1
#define C1 2
#define C2 3
#define A1 4
#define A2 5
#define DG 6
#define SP 7
#define CR 8
#define XP 10
#define XL 11
#define W1 12
#define W2 13
#define W3 14

/* define class -> num mapping */
#define EAR 0
#define NEW 1 
#define SPA 2 

/* define gang mappings */
#define COM 0
#define MED 1
#define SAP 2
#define SCO 3
#define TEC 4
#define HIG 5
#define ENG 6

/* function prototypes for PC generation */

void roll_pc(int world, int regiment);

void change_stat(int stat, int sincr, int s_or_p);

void print_stats();

void print_2stats();

void print_name();

void print_status();

void gen_secondary_stats();

void get_pcname();

void print_pc();

int move_pc(int x, int y);

int get_from_flr();

#endif
