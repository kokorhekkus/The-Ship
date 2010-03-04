#include "rtutil.h"
#include "engine.h"

#include <stdio.h>

/* convert an integer to a string */
char *inttostr(int num) {
	static char str[4];
	sprintf(str, "%d", num);
	return str;
}

void rtlog(char *msg) {
	FILE *fp = fopen('./rt.log', 'a+');
	if (fp == NULL) {
		error_exit("Can't open file for logging");
	} else {
		if (fprintf(fp, msg) < 0) {
			error_exit("Can't write to log file");
		}
	}
}
