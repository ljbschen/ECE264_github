#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "answer06.h"

/*
char a[5][5] = {
	{'X','X','X',' ','X'},
	{'X',' ',' ',' ','X'},
	{'X',' ','X',' ','X'},
	{'X',' ','X',' ','X'},
	{'X','X','X',' ','X'}

};*/

int main(int argc, char * * argv) {
	FILE *fp;
	char c;
	char **a;
	
	a = (char *)malloc(7);
	int j = 0;
	while (j<7) {
		a[j++] = (char)malloc(9);
	}
	int w = 0;
	int h = 0;
	if ( (fp = fopen("sampel.2.9x7", "r")) ) {
		while ( (c = fgetc(fp)) != EOF ) {
			a[h][w++] = c;
			if (w == 9) {
				w = 0;
				h++;
			}
		}
		fclose (fp);
	}

    printf("Welcome to PA06.\n"	   "\n");
    j = 0;
    while (j<7) {
    	printf("%s", a[j-1]);
    }
    print_directions(a, 9, 7);

    j = 0;
    while (j<7) {
		free(a[j++]);
	}
	free(a);
    return 1;
}