#include "rtutil.h"

#include <stdio.h>

/* convert an integer to a string */
char *inttostr(int num) {
    static char str[4];
	sprintf(str, "%d", num);
	return str;
}
