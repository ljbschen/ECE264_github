#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "answer05.h"

void partitionAll(int value) {
	//need an index to trace the location in the array
	int IntArr[value];
	int colIndex = 0;
	void f(int remain) {
		//start a new array when remainer is 0
		if (remain == 0) {
			//print out current row
			int j;
			for (j = 0; j < colIndex; j++ ) {
				if (j == 0) printf ("= %d", IntArr[j]);
				else printf (" + %d", IntArr[j]);
			}
			printf("\n");
		}
		//go to for-loop for any other cases
		else {
			int i;
			//need a local index to trace the beginning position of current for loop index
			int col = colIndex;
			for (i = remain; i > 0; i --) {
				//take down the current number 
				IntArr[colIndex++] = i;
				//and then patition it
				f(remain - i);
				//determine if we need to copy the current numbers
				//under flowing condition we need to copy the numbers up to current colIndex
				//1. i is not 1, which means we can still patition current remainer
				//2. && current colIndex is not 0
				if ( colIndex != 0 && i != 1 ) {
					int j ;
					//go through each int and copy to next row
					for (j = col; j < colIndex; j ++){
						IntArr[j] = 0;
					}
				}
				//once complete current remain, return to the beginning position of current for loop index
				colIndex = col;
			}
		}
	}
	//call recursion
	f(value);
	printf("\n");		
}

void partitionIncreasing(int value) {
	//need an index to trace the location in the array
	bool isIncreasing = true;
	int IntArr[value];
	int colIndex = 0;
	void f(int remain) {
		//start a new array when remainer is 0
		if (remain == 0 ) {
			if (isIncreasing) {
				//print out current row
				int j;
				for (j = 0; j < colIndex; j++ ) {
					if (j == 0) printf ("= %d", IntArr[j]);
					else printf (" + %d", IntArr[j]);
				}
				printf("\n");
			}
			else isIncreasing = true;
		}
		//go to for-loop for any other cases
		else {
			int i;
			//need a local index to trace the beginning position of current for loop index
			int col = colIndex;
			for (i = remain; i > 0; i --) {
				//take down the current number 
				if (colIndex != 0) isIncreasing &= (i > IntArr[colIndex - 1]) ;
				IntArr[colIndex++] = i;
				//and then patition it
				f(remain - i);
				//determine if we need to copy the current numbers
				//under flowing condition we need to copy the numbers up to current colIndex
				//1. i is not 1, which means we can still patition current remainer
				//2. && current colIndex is not 0
				if ( colIndex != 0 && i != 1 ) {
					int j ;
					isIncreasing = true;
					//go through each int and copy to next row
					for (j = 1; j < col; j ++) {
						isIncreasing &= (IntArr[j] > IntArr[colIndex - 1]);
					}
					for (j = col; j < colIndex; j ++){
						IntArr[j] = 0;
					}
				}
				//once complete current remain, return to the beginning position of current for loop index
				colIndex = col;
			}
		}
	}
	//call recursion
	f(value);
	printf("\n");		
}
	
void partitionDecreasing(int value) {
	//need an index to trace the location in the array
	bool isDecreasing = true;
	int IntArr[value];
	int colIndex = 0;
	void f(int remain) {
		//start a new array when remainer is 0
		if (remain == 0 ) {
			if (isDecreasing) {
				//print out current row
				int j;
				for (j = 0; j < colIndex; j++ ) {
					if (j == 0) printf ("= %d", IntArr[j]);
					else printf (" + %d", IntArr[j]);
				}
				printf("\n");
			}
			else isDecreasing = true;
		}
		//go to for-loop for any other cases
		else {
			int i;
			//need a local index to trace the beginning position of current for loop index
			int col = colIndex;
			for (i = remain; i > 0; i --) {
				//take down the current number 
				if (colIndex != 0) isDecreasing &= (i < IntArr[colIndex - 1]) ;
				IntArr[colIndex++] = i;
				//and then patition it
				f(remain - i);
				//determine if we need to copy the current numbers
				//under flowing condition we need to copy the numbers up to current colIndex
				//1. i is not 1, which means we can still patition current remainer
				//2. && current colIndex is not 0
				if ( colIndex != 0 && i != 1 ) {
					int j ;
					isDecreasing = true;
					for (j = 1; j < col; j ++) {
						isDecreasing &= ( IntArr[j] < IntArr[colIndex - 1]);
					}
					//go through each int and copy to next row
					for (j = col; j < colIndex; j ++){
						IntArr[j] = 0;
					}
				}
				//once complete current remain, return to the beginning position of current for loop index
				colIndex = col;
			}
		}
	}
	//call recursion
	f(value);
	printf("\n");	
}

void partitionOdd(int value) {//need an index to trace the location in the array
	bool isOdd = true;
	int IntArr[value];
	int colIndex = 0;
	void f(int remain) {
		//start a new array when remainer is 0
		if (remain == 0 ) {
			if (isOdd) {
				//print out current row
				int j;
				for (j = 0; j < colIndex; j++ ) {
					if (j == 0) printf ("= %d", IntArr[j]);
					else printf (" + %d", IntArr[j]);
				}
				printf("\n");
			}
			else isOdd = true;
		}
		//go to for-loop for any other cases
		else {
			int i;
			//need a local index to trace the beginning position of current for loop index
			int col = colIndex;
			for (i = remain; i > 0; i --) {
				//take down the current number 
				isOdd &= ((i % 2) == 1) ;
				IntArr[colIndex++] = i;
				//and then patition it
				f(remain - i);
				//determine if we need to copy the current numbers
				//under flowing condition we need to copy the numbers up to current colIndex
				//1. i is not 1, which means we can still patition current remainer
				//2. && current colIndex is not 0
				if ( colIndex != 0 && i != 1 ) {
					int j ;
					for (j = 0; j < col; j ++) {
						isOdd &= (( IntArr[j] % 2) == 1);
					}
					//go through each int and copy to next row
					for (j = col; j < colIndex; j ++){
						IntArr[j] = 0;
					}
				}
				//once complete current remain, return to the beginning position of current for loop index
				colIndex = col;
			}
		}
	}
	//call recursion
	f(value);
	printf("\n");	


}

void partitionEven(int value) {
	if (value % 2 == 1) return;
	bool isEven = true;
	int IntArr[value];
	int colIndex = 0;
	void f(int remain) {
		//start a new array when remainer is 0
		if (remain == 0 ) {
			if (isEven) {
				//print out current row
				int j;
				for (j = 0; j < colIndex; j++ ) {
					if (j == 0) printf ("= %d", IntArr[j]);
					else printf (" + %d", IntArr[j]);
				}
				printf("\n");
			}
			else isEven = true;
		}
		//go to for-loop for any other cases
		else {
			int i;
			//need a local index to trace the beginning position of current for loop index
			int col = colIndex;
			for (i = remain; i > 0; i --) {
				//take down the current number 
				isEven &= ((i % 2) == 0) ;
				IntArr[colIndex++] = i;
				//and then patition it
				f(remain - i);
				//determine if we need to copy the current numbers
				//under flowing condition we need to copy the numbers up to current colIndex
				//1. i is not 1, which means we can still patition current remainer
				//2. && current colIndex is not 0
				if ( colIndex != 0 && i != 1 ) {
					int j ;
					for (j = 0; j < col; j ++) {
						isEven &= (( IntArr[j] % 2) == 0);
					}
					//go through each int and copy to next row
					for (j = col; j < colIndex; j ++){
						IntArr[j] = 0;
					}
				}
				//once complete current remain, return to the beginning position of current for loop index
				colIndex = col;
			}
		}
	}
	//call recursion
	f(value);
	printf("\n");	
}

void partitionOddAndEven(int value) {
	bool isOE = true;
	int IntArr[value];
	int colIndex = 0;
	void f(int remain) {
		//start a new array when remainer is 0
		if (remain == 0 ) {
			if (isOE) {
				//print out current row
				int j;
				for (j = 0; j < colIndex; j++ ) {
					if (j == 0) printf ("= %d", IntArr[j]);
					else printf (" + %d", IntArr[j]);
				}
				printf("\n");
			}
			else isOE = true;
		}
		//go to for-loop for any other cases
		else {
			int i;
			//need a local index to trace the beginning position of current for loop index
			int col = colIndex;
			for (i = remain; i > 0; i --) {
				//take down the current number 
				if (colIndex > 0) isOE &= ((i % 2) == 0) ^ ((IntArr[colIndex - 1] % 2) == 0) ;
				IntArr[colIndex++] = i;
				//and then patition it
				f(remain - i);
				//determine if we need to copy the current numbers
				//under flowing condition we need to copy the numbers up to current colIndex
				//1. i is not 1, which means we can still patition current remainer
				//2. && current colIndex is not 0
				if ( colIndex != 0 && i != 1 ) {
					int j ;
					for (j = 1; j < col; j ++) {
						isOE &= ((IntArr[j] % 2) == 0) ^ ((IntArr[ j - 1] % 2) == 0) ;
					}
					//go through each int and copy to next row
					for (j = col; j < colIndex; j ++){
						IntArr[j] = 0;
					}
				}
				//once complete current remain, return to the beginning position of current for loop index
				colIndex = col;
			}
		}
	}
	//call recursion
	f(value);
	printf("\n");	

}

void partitionPrime(int value) {
	bool isPrime = true;
	int IntArr[value];
	int colIndex = 0;

	bool Prime (int i) {
		if (i == 1) return false;
		int p;
		for (p = 2; p < i; p ++) {
			if ( i % p == 0) return false;
		}
		return true;
	}

	void f(int remain) {
		//start a new array when remainer is 0
		if (remain == 0 ) {
			if (isPrime) {
				//print out current row
				int j;
				for (j = 0; j < colIndex; j++ ) {
					if (j == 0) printf ("= %d", IntArr[j]);
					else printf (" + %d", IntArr[j]);
				}
				printf("\n");
			}
			else isPrime = true;
		}
		//go to for-loop for any other cases
		else {
			int i;
			//need a local index to trace the beginning position of current for loop index
			int col = colIndex;
			for (i = remain; i > 0; i --) {
				//take down the current number 
				if (i != 2) isPrime &= Prime(i) ;
				IntArr[colIndex++] = i;
				//and then patition it
				f(remain - i);
				//determine if we need to copy the current numbers
				//under flowing condition we need to copy the numbers up to current colIndex
				//1. i is not 1, which means we can still patition current remainer
				//2. && current colIndex is not 0
				if ( colIndex != 0 && i != 1 ) {
					int j ;
					for (j = 0; j < col; j ++) {
						if (IntArr[j] != 2) isPrime &= Prime(IntArr[j]) ;
					}
					//go through each int and copy to next row
					for (j = col; j < colIndex; j ++){
						IntArr[j] = 0;
					}
				}
				//once complete current remain, return to the beginning position of current for loop index
				colIndex = col;
			}
		}
	}
	//call recursion
	f(value);
	printf("\n");	

}