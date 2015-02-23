#include "answer03.h"
#include <string.h>

char * strcat_ex(char * * dest, int * n, const char * src) {
	int dest_len = 0;
	int src_len = 0;
	if ( * dest == NULL ) {
        * n = 0;
        dest_len = 0;
    }
	else dest_len = strlen( * dest);
    if ( src == NULL )	return * dest;
    else src_len = strlen(src);
    if ( dest_len + src_len + 1 > * n ) {
        char * newbuffer;
       	//(1) malloc a new buffer of size 1 + 2 * (strlen(*dest) + strlen(src))	
    	newbuffer = (char *) malloc(1 + 2 * (dest_len + src_len));
    	//(2) set '*n' to the size of the new buffer
    	*n = (1 + 2 * (dest_len + src_len));
    	//(3) copy '*dest' into the beginning of the new buffer
        if (dest_len != 0) strcpy(newbuffer, *dest);
    	//(4) free the memory '*dest', and then set '*dest' to point to the new buffer     
        free(*dest);
        *dest = newbuffer;
    }
    	//(5) concatenate 'src' onto the end of '*dest'.
    char * temp;
    temp = *dest;
    if (dest_len != 0) {
        while (*temp) temp++;
    }
    while ((*temp++ = *src++) != '\0')  
        ;
    return *dest;
}

char * * explode(const char * str, const char * delims, int * arrLen) {
    //find out how many delims in the str
    int N = 0;
    int i;
    int len = 0;
    if (str == NULL) return NULL;
    else len = strlen(str);

    for (i = 0; i < len; i ++) {
        if (strchr(delims, str[i]) != NULL) N++;
    }
    *arrLen = N + 1;

    // Create the return array
    char * * strArr = malloc((N + 1) * sizeof(char *));

    //then strcpy into different location
    //create two indicies: last and ind
    //last traces the position of last observed delim and ind traces the current char in str

    int last = -1;

    //go through all chars in str and if it is a delim :
    //1. create a string for the char from last to ind
    //2. set last to current ind
    for (i = 0; i < len; i++){
        if (strchr(delims, str[i]) != NULL) {
            *strArr = (char *)malloc(i - last);
            strncpy(*strArr, str + last + 1, i - last - 1);
            (*strArr)[i - last - 1] = '\0';
            strArr++;
            last = i;   
        }
    }
    
    //add the last string
    *strArr = (char *) malloc (len - last);
    strncpy(*strArr, str + last + 1, len - last -1);
    (*strArr)[len - last - 1] = '\0';
    
    //restore strArr to the first cell of array
    strArr = strArr - N;
    
    return strArr;
}

char * implode(char * * strArr, int len, const char * glue){
    //first need to figure out how many chars are in the strArr
    int N = 0;
    int i;
    int j;
    for (i = 0; i < len; i++) {
        for (j = 0; j < strlen(strArr[i]); j++){
            if ( (strArr [i])[j] !=  '\0' ) N++;
        }
    }
    //then add the total number of glue
    N = N + strlen(glue) * (len - 1);
    //malloc mem for str
    char * str = (char *) malloc (N + 1);
    //copy strArr into str and add glue 
    //at every end of elements in strArr
    for (i = 0; i < len; i++) {
        if (i == 0) strcpy (str, *strArr);
        else strcat(str, strArr[i]);
        if (i != len - 1) strcat(str, glue);
    }
    //add "\0"
    str[N] = '\0';
    return str;
}

void sortStringArray(char * * arrString, int len){
    int compare(const void * p1, const void * p2){
        int i = 0;
        const char ** a = (const char **) p1;
        const char ** b = (const char **) p2;
        if ( **a == '\0' ) return -1;
        if ( **b == '\0' ) return 1;
        while ((*a)[i] ==  (*b)[i]) {
            i ++;
            if ((*a)[i] == '\0') return -1;
            if ((*b)[i] == '\0') return 1;
        }
        return ((*a)[i] - (*b)[i]);
    }
    qsort(arrString, len, sizeof(char **), compare);
}

void sortStringCharacters(char * str){
    if ( str == NULL ) return ;
    int compare(const void * p1, const void * p2){
        const char * a = (const char *) p1;
        const char * b = (const char *) p2;
        return (*a - *b);
    }
    qsort(str, strlen(str), sizeof(char), compare);
}

void destroyStringArray(char * * strArr, int len){
    int i;
    for (i = 0; i < len; i ++){
        free(*(strArr++));
    }
    free(strArr - len);
}

