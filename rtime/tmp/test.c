#include <stdio.h>

main() {

	char *msg = "Cunt";

	FILE *fp = fopen("./rt.log", "a+");
	if (fp == NULL) {
		printf("Can't open file for logging");
	} else {
	  if (fprintf(fp, "%s", msg) < 0) {
			printf("Can't write to log file");
		}
	}
	fclose(fp);
}