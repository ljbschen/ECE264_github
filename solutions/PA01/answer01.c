#include <stdlib.h>
#include "answer01.h"
/*
Passed all testcases
*/
int arraySum(int * array, int len)
{
    int sum = 0;
    int i;
    for (i = 0; i < len; ++i)  	sum = sum + array[i];
    return sum;
}

int arrayCountNegative(int * array, int len)
{
    int NegativeCounter = 0;
    int i;
    for (i = 0; i < len; ++i) 
    {
	if (array[i] < 0) NegativeCounter++;
    } 
    return NegativeCounter;
}

int arrayIsIncreasing(int * array, int len)
{   
    if (len == 0) return 1;
    int i;
    for (i = 1 ; i < len; i++)
    {
        if  (array[i] < array[i-1]) return 0;
    }
    return 1; 
}

int arrayIndexRFind(int needle, const int * haystack, int len)
{
     int index = -1;
    int i;
    for (i = 0; i < len; i++)
    {
        if (haystack[i] == needle) index = i; 
    }

        return index;
}

int arrayFindSmallest(int * array, int len)
{   
    int min = 0;
    int i;
    for (i = 1; i < len; i++)
    {
	if (array[i] < array[min]) min = i;
    }
    return min;
}
