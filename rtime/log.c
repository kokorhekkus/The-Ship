#include "log.h"
#include "engine.h"
#include "rtutil.h"

#include <time.h>
#include <stdio.h>

/* initialise, and print time of day to logfile */
/* TODO: Lots... */
int init_log() {

  rtlog(gettimestr());

  return 1;
}

/* log to a file */
void rtlog(char *msg) {

    FILE *fp = fopen("./rt.log", "a+");
	if (fp == NULL) {
		error_exit("Can't open file for logging");
	} else {
	  if (fprintf(fp, "%s\n", msg) < 0) {
			error_exit("Can't write to log file");
		}
	}
	fclose(fp);
}

/* returns a string containing the current time */
char *gettimestr() {
  time_t curtime;
  char curftime[64];

  curtime = time(NULL);
  sprintf(curftime, "%s", ctime(&curftime));

  return curftime;
}
