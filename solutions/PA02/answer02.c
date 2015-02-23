#include <stdlib.h>
#include "answer02.h"

size_t my_strlen(const char * str)
{
	int len = 0;
	while (*str != '\000')
	{
		len ++;
		str ++;
	}
	return len;
}


int my_countchar(const char * str, char ch)
{
	int counter = 0;
	while (*str != '\000')
	{
		if (*str == ch) counter ++;
		str ++;
	}
	return counter;
}


char * my_strchr(const char * str, int ch)
{
	while (*str != '\000')
	{
		if (*str == ch) return (char *) str;
		str ++;
	}
	if (ch == '\000') return (char *) str;
	return NULL;

}
char * my_strrchr(const char * str, int ch)
{
	char * ptr = NULL;
        while (*str != '\000')
        {
		//waring, assign const to non-const
                if (*str == ch) ptr = str;
                str ++;
        }
	//waring, assign const to non-const 
        if (ch == '\000') ptr = str;
        return ptr;
}

char * my_strstr(const char * haystack, const char * needle)
{
	//return current string if input is empty
	if (*needle == '\000') return (char *) haystack;

	//local pointer points to the first occrrence
	char * ptr = NULL;

	//local copy of the first element in needle, will be used to reset
	
	const char * tempneedle = needle;
	
	//go through haystack to compare
	while (*haystack != '\000')
	{
		//set ptr to the current str
		//when str matches needle
		//and ptr has not been set
		if ((*haystack == *needle)&&(ptr == NULL)) ptr = haystack;
		
		//increse haystack and needle to compare the next char
		//once reach the end of needle then return ptr
		if (*needle == '\000') return ptr;
		if (*haystack == *needle)
		{
			needle++;
			haystack ++;
		}
		
		//or reach mismatch then reset needle and ptr
		else 
		{
			needle = tempneedle;
			ptr = NULL;
			haystack ++;
		}
	}
	return ptr;
}

char * my_strcpy(char * dest, const char * src)
{
	//make a copy of the pointer that points to the first char
	char * temp = dest;
	//get the length of the src
	int len;
	int i;
	len = my_strlen(src);
	//take the value of src as an address, 
	//get the value at that address, *src
	//assign that to the address that represented by the value of 
	//dest, *dest
	for (i = 0; i < len; ++i)
	{
		* dest = * src;
		dest ++;
		src ++;
	}
	//insert the '/0' to terminate the string
	* dest = '\000';
	//return the pointer that points to the first char
	return (char *) temp;
}

char * my_strcat(char * dest, const char * src)
{
	//make a copy of the pointer
	char * temp = dest;
	while (*dest != '\000')	dest ++;
       
	//start to insert new chars 
	while (*src != '\000')
	{
		* dest = * src;
		dest ++;
		src ++;
	}
        * dest = '\000';
	return temp;
}

int my_isspace(int ch)
{
	if ((ch >= 9)&&(ch <= 13)) return 1;
	if (ch == ' ') return 1;
	return 0;
}

int my_atoi(const char * str)
{
	int ret = 0;
	int neg = 0;
	
	//condition 1, skip all white spaces
	while (my_isspace(*str)) str ++;
        //condition 2, "-" sign
        if (*str == '-') 
	{
		neg = 1;
		str ++;
	}
	//condition 3, non-int
	if ((*str < 48)||(*str > 57)) return 0;
	//int, increment to read next char
	while ((*str >= 48)&&(*str <= 57))
	{
		ret = ret * 10 + (*str - 48);
		str ++;
	}
	if (neg) return - ret;
	return ret;
}
