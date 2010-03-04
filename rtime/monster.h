#ifndef RT_MONSTER
#define RT_MONSTER 1

typedef struct monster {

	/* pointer to next monster in list, and unique key */
	struct monster *next_mon;
	int unum;

	char *name;
	int life;
	int conc;
	int speed;
	int dodge;
	int arm1;
	int arm2;
	int xloc;
	int yloc;

} monster;

/* monster manipulation function prototypes */

/* linked list stuff */

monster *insert_mon(monster *mlist_ptr, monster *mon_ptr);

int delete_mon(monster *mlist_ptr, int mon_num);

void init_monsters();

int monster_present(monster *mlist_ptr, int x, int y);

void gen_level_mon(int type, int depth);

#endif
