
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "answer03.h"


int main(int argc, char * * argv) {
    printf("Welcome to PA03.\n"
	   "\n");
    
    printf("Print out some memory addresses for argc, argv...\n"
	   "to illustrate how memory is laid out.\n");
    printf("&argc = %p\n", &argc);
    printf("&argv = %p\n", &argv);
    printf("argv = %p\n", argv);
    printf("*argv = %p\n", *argv);
    printf("*argv = %s\n", *argv);
    printf("**argv = %c\n", **argv);

    // Let's create our own array of strings
    printf("\nTesting strcat_ex(...)\n");
    char * str1 = malloc(5);    // allocate an initial buffer
    int n = 5;                 
    strcpy( str1, "one" ); 
    char * str2 = malloc(5);
    strcpy( str2, "two" );
    printf("Before strcat_ex, str1 == %p (%s),"
	   "str2 == %p (%s)\n", str1, str1, str2, str2);
    strcat_ex(&(str1), &n, str2);
    printf("After swap, str1 == %p (%s), "
	   "str2 == %p (%s)\n", str1, str1, str2, str2);

    free (str1);
    free (str2);

    
    printf("\nTesting explode(...)\n");
    char *str3 = malloc(40);
    //char *str4 = malloc(20);
    strcpy(str3, "one\ttwo\vthree\nfour\nfive\rsix\fs") ;
    //strncpy(str4, str3 + 3, 5);
    int len = 0;
    char * * strArr = explode(str3, " \t\v\n\r\f", &len);
    //printf("%p (%s)\n", *strArr, *strArr);
    printf("The origin string is %s (%p).\nThe delims are (/t/v/n/r/f)."
        "\nAfter split we have %i (%p) substrings.\nAnd they are: \n", str3, str3, len, &len);
    int i;
    for (i = 0; i < len; i ++){
        printf("%s (%p)\n", *(strArr + i), *(strArr + i));
    }
    free(str3);
    
    printf("\nTesting implode(...)\n");
    char * str4 = implode(strArr, len, ", ");
    printf("(%s)\n", str4); 

    printf("\nTesting sortStringArray(...)\n");
    char * * strArr2 = malloc(len * sizeof(char*));
    char * str5 = malloc (20);

    strcpy(str5, "lady,beatle,brew");

    strArr2 = explode(str5, ",", &len); 
    
    printf("%s\n", str5);
    sortStringArray(strArr2, len);
    printf("After sort, we have:\n");
    printf("%s\n%s\n%s\n", strArr2[0],strArr2[1],strArr2[2]);

    free(strArr2);

    free (str4);
    //free strArr
    for (i = 0; i < len; i ++){
        free(*(strArr++));
    }
    free(strArr - len);

    return EXIT_SUCCESS;
}


