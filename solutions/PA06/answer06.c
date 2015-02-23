#include "answer06.h"
#include <stdio.h>

int countspace(char **a, int rows, int cols) {
	int i;
	int j;
	int counter = 0;
	for (i = 0; i< rows; i++) {
		for (j = 0; j < cols; j++) {
			if (a[i][j] == ' ') counter++;
		}
	}
	return counter;
}

void walkmaze(char **a, int *rowIndex, int *colIndex, int rows, int cols, char indicator, char *dir, int *step) {
	char track = ' ';
	if (indicator == ' ') track = '+';
	if (indicator == '+') track = 'X'; 
	//first part takes care of the normal path recursion.
	//S
	if(*rowIndex<rows-1 	 &&a[*rowIndex+1][*colIndex] == indicator) {
		//leave the track at current position
		a[(*rowIndex)++][*colIndex] = track;
		if ((*dir) == 'S') {(*step)++;}
		else {
			printf("%c %d\n", *dir, *step);
			*dir = 'S';
			*step = 1;
		}
		return ;
	}
	//N
	if(*rowIndex>1		 &&a[*rowIndex-1][*colIndex] == indicator) {
		//leave the track at current position
		a[(*rowIndex)--][*colIndex] = track;
		if ((*dir) == 'N') {(*step)++;}
		else {
			printf("%c %d\n", *dir, *step);
			*dir = 'N';
			*step = 1;
		}
		return ;
	}	
	//W
	if(*colIndex>1		 &&a[*rowIndex][*colIndex-1] == indicator) {
		//leave the track at current position
		a[*rowIndex][(*colIndex)--] = track;
		if ((*dir) == 'W') {(*step)++;}
		else {
			printf("%c %d\n", *dir, *step);
			*dir = 'W';
			*step = 1;
		}
		return ;
	}	
	//E
	if(*colIndex<cols-1     &&a[*rowIndex][*colIndex+1] == indicator) {
		//leave the track at current position
		a[*rowIndex][(*colIndex)++] = track;
		if ((*dir) == 'E') {(*step)++;}
		else {
			printf("%c %d\n", *dir, *step);
			*dir = 'E';
			*step = 1;
		}
		return ;
	}
}

void mazehelper(char **a, int rowIndex, int colIndex, int rows, int cols, char *dir, int *step) {
	//count space to check if we reach the deadend
	int counter = 0;
	if(rowIndex<rows-1 	 &&a[rowIndex+1][colIndex] == ' ') {counter++;}
	if(rowIndex>1 		 &&a[rowIndex-1][colIndex] == ' ') {counter++;}
	if(colIndex>1		 &&a[rowIndex][colIndex-1] == ' ') {counter++;}
	if(colIndex<cols-1   &&a[rowIndex][colIndex+1] == ' ') {counter++;}
	//if the counter is not 0, we take the normal path
	//indicator will be ' '
	if (counter) {
		//char **a, int *rowIndex, int *colIndex, int rows, int cols, char *dir, int *step, char indicator
		walkmaze(a, &rowIndex, &colIndex, rows, cols, ' ', dir, step);
	}
	//if the counter is 0, we take the stepback path
	//indicator will be '+'
	if (counter == 0) {
		walkmaze(a, &rowIndex, &colIndex, rows, cols, '+', dir, step);
	}
	if (countspace(a, rows, cols) != 0) {
		mazehelper(a, rowIndex, colIndex, rows, cols, dir, step);
	}
	//else printf("it's done\n");
}

void print_directions(char** maze, int w, int h) {
	/* YOUR CODE HERE */
	int c = 0;
	//find the entrance first
	while ( (maze[0][c++]) != ' ' ) {;}
	c--;
	char dir = 'S';
	int step = 0;
	mazehelper(maze, 0, c, h, w, &dir, &step);
}