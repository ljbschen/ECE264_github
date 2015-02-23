#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "answer05.h"

int IntArr[1000][1000];
int colIndex = 0;
int rowIndex = 0;

void f(int remain) {
	//start a new array when remainer is 0
	if (remain == 0) {
		rowIndex ++;
	}
	//go to for-loop for any other cases
	else {
		int i;
		int col = colIndex;
		for (i = remain; i > 0; i --) {
			//take down the current number and then patition it
			IntArr[rowIndex][colIndex++] = i;
			f(remain - i);
			colIndex = col;
			if ( colIndex != 0 && i != 1 ) {
				int j = 0;
				for (j = 0; j < colIndex; j ++){
					IntArr[rowIndex][j] = IntArr[rowIndex - 1][j];
				}
			}
		}
	}
}

int main(int argc, char * * argv) {	
	int i;
	int j;
	printf("%i", atoi(argv[1]));

	f(atoi(argv[1]));

	for (i = 0; i < 1000; i++) {
		if (IntArr[i][0] == 0) break;
		printf("\n    = ");
		for (j = 0; j < 1000; j++ ) {
			if (IntArr[i][j] == 0) break;
			if (j == 0) printf (" %d", IntArr[i][j]);
			else printf (" + %d", IntArr[i][j]);
		}
		
	}
	printf("\n");
	return EXIT_SUCCESS;
}