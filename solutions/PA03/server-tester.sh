#!/bin/bash

PA03=PA03
FILES="answer03.c"

# TAs may be reset by the CREATE-TESTER.sh script
TAS=""

# The marking script should call suppress mark
SUPPRESS_MARK=0
[ "$1" == "--suppress-grade" ] && SUPPRESS_MARK=1

# These are the files that will be embedded for marking
EMBED="answer03.h test.c"

# EMBED FUNCTIONS HERE
TAS="DEFINE_QUICK_TESTER"

echo_answer03_h()
{
cat <<ENDEOF
#ifndef PA03_H
#define PA03_H 

#include <stdlib.h>

/**
 * Append the C-string 'src' to the end of the C-string '*dest'.
 *
 * strcat_ex(...) will append the C-string 'src' to the end of the string
 * at '*dest'. The parameter 'n' is the address of a int that specifies how
 * many characters can safely be stored in '*dest'. 
 *
 * If '*dest' is NULL, or if '*dest' is not large enough to contain the result
 * (that is, the sum of the lengths of *dest, src, and the null byte), then
 * strcat_ex will:
 * (1) malloc a new buffer of size 1 + 2 * (strlen(*dest) + strlen(src))
 * (2) set '*n' to the size of the new buffer
 * (3) copy '*dest' into the beginning of the new buffer
 * (4) free the memory '*dest', and then set '*dest' to point to the new buffer
 * (5) concatenate 'src' onto the end of '*dest'.
 *
 * Always returns *dest.
 *
 * Why do we need to pass dest as char * *, and n as int *? 
 * Please see the FAQ for an answer.
 *
 * Hint: These <string.h> functions will help: strcat, strcpy, strlen.
 * Hint: Leak no memory.
 */
char * strcat_ex(char * * dest, int * n, const char * src);

/**
 * Takes a string and splits it into an array of strings according to delimiter.
 * The memory location '*arrLen' is initialized to the length of the returned
 * array.
 *
 * str: A string to split
 * delims: a string that contains a set of delimiter characters. explode(...) 
 *         will split the string at any character that appears in 'delims'.
 * arrLen: pointer to an int that is used to store the resultant length of the
 *         returned array.
 *
 * For example, if delimiter is white space " \\t\\v\\n\\r\\f", then,
 * int len;
 * char * * strArr = explode("The\\nTuring test", " \\t\\v\\n\\r\\f", &len);
 * // len = 3, strArr[0] is "The", strArr[1] is "Turing", strArr[2] is "test"
 *
 * Hint: you can use <string.h> functions "memcpy" and "strchr"
 *       "memcpy" copies blocks of memory.
 *       "strchr" can be used to tell if a specific character is in delims.
 * Hint: this question is hard; it will help to draw out your algorithm.
 * Hint: read the FAQ...
 */
char * * explode(const char * str, const char * delims, int * arrLen);

/**
 * Takes an array of strings, and concatenates the elements into a single
 * string, placing 'glue' between each successive element.
 *
 * strArr: an array of strings
 * len: the length of the array 'strArr'
 * glue: string to concatenate between each element of 'strArr'
 *
 * For example:
 * int len;
 * char * * strArr = explode("100 224 147 80", " ", &len);
 * char * str = implode(strArr, len, ", ");
 * printf("(%s)\\n", str); // (100, 224, 147, 80)
 *
 * Hint: use strcat_ex in a for loop.
 */
char * implode(char * * strArr, int len, const char * glue);

/**
 * Takes an array of C-strings, and sorts them alphabetically, ascending.
 *
 * arrString: an array of strings
 * len: length of the array 'arrString'
 *
 * For example, 
 * int len;
 * char * * strArr = explode("lady beatle brew", " ", &len);
 * sortStringArray(strArr, len);
 * char * str = implode(strArr, len, " ");
 * printf("%s\\n", str); // beatle brew lady
 *
 * Hint: use the <stdlib.h> function "qsort"
 * Hint: you must _clearly_ understand the typecasts.
 */
void sortStringArray(char * * arrString, int len);

/**
 * Sorts the characters in a string.
 *
 * str: string whose characters are to be sorted
 *
 * For example, 
 * char * s1 = strdup("How did it get so late so soon?");
 * sortStringCharacters(s1)
 * // s1 is now "       ?Haddeegiilnooooossstttw"
 *
 * Hint: use the <stdlib.h> function "qsort"
 * Hint: you must _clearly_  understand the typecasts.
 */
void sortStringCharacters(char * str);

/**
 * Safely frees all memory associated with strArr, and then strArr itself.
 * Passing NULL as the first parameter has no effect.
 *
 * strArr: an array of strings
 * len: the length of 'strArr'
 *
 * int len;
 * const char * abe = "Give me six hours to chop down a tree and I will spend\\n"
 *                    "the first four sharpening the axe.";
 * char * * strArr = explode(abe, "\\n ");
 * destroyStringArray(strArr, len); // cleans memory -- no memory leaks
 * destroyStringArray(NULL, 0); // does nothing, does not crash.
 */
void destroyStringArray(char * * strArr, int len);

#endif
ENDEOF
}


echo_test_c()
{
cat <<ENDEOF

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
 
#include "answer03.h"

static void print_packed(const char * s)
{
    while(*s) {
	switch(*s) {
	case '\$': printf("\$"); break;
	case '\\'': printf("\\\\'"); break;
	case '\\"': printf("\\\\\\""); break;
	    // case '\\?': printf("\\\\?"); break; not needed
	case '\\\\': printf("\\\\\\\\"); break;
	case '\\0': printf("\\\\0"); break;
	case '\\a': printf("\\\\a"); break;
	case '\\b': printf("\\\\b"); break;
	case '\\f': printf("\\\\f"); break;
	case '\\n': printf("\\\\n"); break;
	case '\\r': printf("\\\\r"); break;
	case '\\t': printf("\\\\t"); break;
	case '\\v': printf("\\\\v"); break;
	default:
	    if(*s < ' ' || *s > '~') 
		printf("\\\\%02x", (int) *s);
	    else
		printf("%c", *s);
	}
	s++;
    }
}

static char * strcat_ex_sol(char * * dest, int * n, const char * src)
{
    int dst_len = *dest == NULL ? 0 : strlen(*dest);
    int src_len = strlen(src);
    if((*dest == NULL) || (src_len + dst_len + 1 > *n)) {
	// Reallocate *dest
	*n = 1 + 2 * (src_len + dst_len);
	char * new_dst = malloc(*n * sizeof(char));	
	*new_dst = '\\0';
	if(*dest != NULL)
	    strcpy(new_dst, *dest);
	free(*dest);
	*dest = new_dst;
    }
    strcat(*dest, src);
    return *dest;
}

static char * * explode_sol(const char * str, const char * delims, int * arrLen)
{
    // Some iterators that we'll use below
    const char * itr, * last;

    // Calculate how many strings we'll need
    *arrLen = 1; // we always have 1 + count(delimiter) strings
    itr = str;
    while(*itr) {
	if(strchr(delims, *itr))
	    (*arrLen)++;
	itr++;
    }
	
    // Allocate our output array
    char * * arr = malloc(*arrLen * sizeof(char *));

    // Reset our iterators and start hunting for strings
    int arrInd = 0;
    int len; // for the length of strings
    last = str;
    itr = str;
    while(*itr) {
	if(strchr(delims, *itr) != NULL) {
	    len = itr - last;
	    arr[arrInd] = malloc((len+1) * sizeof(char));
	    memcpy(arr[arrInd], last, len);
	    arr[arrInd][len] = '\\0';
	    last = itr + 1;
	    ++arrInd;
	}
	++itr;
    }

    // Handle the final string
    len = itr - last;
    arr[arrInd] = malloc((len+1) * sizeof(char));
    memcpy(arr[arrInd], last, len);
    arr[arrInd][len] = '\\0';

    return arr;
}

static char * implode_sol(char * * strArr, int len, const char * glue)
{
    char * ret = NULL;
    int n = 0;
    int ind;
    for(ind = 0; ind < len; ++ind) {
	if(ind > 0)
	    strcat_ex_sol(&ret, &n, glue);
	strcat_ex_sol(&ret, &n, strArr[ind]);
    }
    return ret;
}

static int strcmpvoid(const void * a, const void * b)
{
    return strcmp(*((const char * *) a), *((const char * *) b));
}

static void sortStringArray_sol(char * * arrString, int len)
{
    qsort(arrString, len, sizeof(char*), strcmpvoid);
}

static int charcmpvoid(const void * a, const void * b)
{
    return (int) *((const char *) a) - (int) *((const char *) b);
}

static void sortStringCharacters_sol(char * str)
{
    qsort(str, strlen(str), sizeof(char), charcmpvoid);
}

static void destroyStringArray_sol(char * * strArr, int len)
{
    if(strArr == NULL) return;
    int ind;
    for(ind = 0; ind < len; ++ind) 
	free(strArr[ind]);
    free(strArr);
}

// ---------------------------------------------------- Test functions

const char * z0 = "";
const char * z1 = "The more that you read, the more things you will know. The more that you learn, the more places you'll go.";
const char * z2 = "How did it get so late so soon?";
const char * z3 = 
    "Twas brillig, and the slithy toves\\n"
    "Did gyre and gimble in the wabe:\\n"
    "All mimsy were the borogoves,\\n"
    "And the mome raths outgrabe.\\n"
    "\\n"
    "Beware the Jabberwock, my son!\\n"
    "The jaws that bite, the claws that catch!\\n"
    "Beware the Jubjub bird, and shun\\n"
    "The frumious Bandersnatch!\\n"
    "\\n"
    "He took his vorpal sword in hand:\\n"
    "Long time the manxome foe he sought --\\n"
    "So rested he by the Tumtum tree,\\n"
    "And stood awhile in thought.\\n"
    "\\n"
    "And, as in uffish thought he stood,\\n"
    "The Jabberwock, with eyes of flame,\\n"
    "Came whiffling through the tulgey wood,\\n"
    "And burbled as it came!\\n"
    "\\n"
    "One, two! One, two! And through and through\\n"
    "The vorpal blade went snicker-snack!\\n"
    "He left it dead, and with its head\\n"
    "He went galumphing back.\\n"
    "\\n"
    "And, has thou slain the Jabberwock?\\n"
    "Come to my arms, my beamish boy!\\n"
    "O frabjous day! Callooh! Callay!\\n"
    "He chortled in his joy.\\n"
    "\\n"
    "Twas brillig, and the slithy toves\\n"
    "Did gyre and gimble in the wabe;\\n"
    "All mimsy were the borogoves,\\n"
    "And the mome raths outgrabe.\\n";

#define ERR(msg) { test_err = TRUE; printf("   // Error, %s\\n", msg); }
#define ERRN(msg) { test_err = TRUE; printf("   // Error, %s :: ", msg); }
#define TIDY								\\
    {									\\
	if(test_err) { n_errs++; printf("   Testcase FAILED\\n"); }	\\
	else printf("   (pass.)\\n");					\\
    }

int test_01()
{
    int n_errs = 0;
    printf("\\ntest 01 :: passing NULL to strcat_ex()\\n\\n");
    {
	int test_err = FALSE;
	printf("   const char * z2 = \\"%s\\";\\n", z2);
	printf("   char * s1 = NULL;\\n");
	printf("   int n;\\n");
	printf("   char * s2 = strcat_ex(&s1, &n, z2);\\n");
	char * s1 = NULL;
	int n;
	char * s2 = strcat_ex(&s1, &n, z2);
	printf("   // s1 = %p: \\"%s\\"\\n", s1, s1);
	printf("   // s2 = %p\\n", s2);
	printf("   // n = %d\\n", n);
	if(s1 == NULL) ERR("s1 is still NULL");
	if(s1 != s2) ERR("s1 != s2");
	if(s1 != NULL && strcmp(s1, z2) != 0) {
	    ERRN("strcmp(s1, z2) should be 0");
	    printf("s1 = \\"%s\\", z2 = \\"%s\\"\\n", s1, z2);
	}
	if(n != 1 + 2*strlen(z2)) ERR("n should be 1 + 2 * strlen(z2)");
	free(s1);
	TIDY;
    }
    return n_errs;
}

int test_02()
{
    int n_errs = 0;
    printf("\\ntest 02 :: passing NULL to strcat_ex()\\n\\n");
    {
	int test_err = FALSE;
	printf("   const char * z0 = \\"\\";\\n");
	printf("   char * s1 = NULL;\\n");
	printf("   int n;\\n");
	printf("   char * s2 = strcat_ex(&s1, &n, z0);\\n");
	char * s1 = NULL;
	int n;
	char * s2 = strcat_ex(&s1, &n, z0);
	printf("   // s1 = %p: \\"%s\\"\\n", s1, s1);
	printf("   // s2 = %p\\n", s2);
	printf("   // n = %d\\n", n);	
	if(s1 == NULL) ERR("s1 is still NULL");
	if(s1 != s2) ERR("s1 != s2");
	if(s1 != NULL && strcmp(s1, z0) != 0) {
	    ERRN("strcmp(s1, z0) should be 0");
	    printf("s1 = \\"%s\\", z0 = \\"%s\\"\\n", s1, z0);
	}
	if(n != 1 + 2*strlen(z0)) ERR("n should be 1 + 2 * strlen(z0)");
	free(s1);
	TIDY;
    }
    return n_errs;
}

int test_03()
{
    int n_errs = 0;
    printf("\\ntest 03 :: no reallocate\\n\\n");
    {
	int test_err = FALSE;
	printf("   const char * z2 = \\"%s\\";\\n", z2);
	printf("   int n = 2048;\\n"
	       "   char * s1 = malloc(n);\\n"
	       "   char * s3 = s1; // keep a copy\\n"
	       "   s1[0] = '\\\\0';\\n"
	       "   char * s2 = strcat_ex(&s1, &n, z2);\\n");
	int n = 2048;
	char * s1 = malloc(n);
	s1[0] = '\\0';
	char * s3 = s1; // backup pointer
	char * s2 = strcat_ex(&s1, &n, z2);
	printf("   // s1 = %p: \\"%s\\"\\n", s1, s1);
	printf("   // s2 = %p\\n", s2);
	printf("   // s3 = %p\\n", s3);
	printf("   // n = %d\\n", n);
	if(s1 == NULL) ERR("s1 is still NULL");
	if(s1 != s2) ERR("s1 != s2");
	if(s1 != s3) ERR("s1 changed in strcat_ex(...) when it shouldn't have");
	if(n != 2048) ERR("n should not change");
	if(s1 != NULL && strcmp(s1, z2) != 0) {
	    ERRN("strcmp(s1, z2) should be 0");
	    printf("s1 = \\"%s\\", z2 = \\"%s\\"\\n", s1, z2);
	}
	free(s1);
	TIDY;
    }
    return n_errs;
}

int test_04()
{
    int n_errs = 0;
    printf("\\ntest 04 :: force reallocate\\n\\n");
    {
	int test_err = FALSE;
	const char * s0 = "Hal, ";
	printf("   const char * z2 = \\"%s\\";\\n", z2);
	printf("   const char * s0 = \\"%s\\";\\n", s0);
	printf("   char * s1 = strdup(s0);\\n"
	       "   int n = strlen(s0);\\n"
	       "   char * s2 = strcat_ex(&s1, &n, z2);\\n");
	int n = strlen(s0);
	char * s1 = strdup(s0);
	char * s2 = strcat_ex(&s1, &n, z2);
	printf("   // s1 = %p: \\"%s\\"\\n", s1, s1);
	printf("   // s2 = %p\\n", s2);
	printf("   // n = %d\\n", n);
	if(s1 == NULL) ERR("s1 is still NULL");
	if(s1 != s2) ERR("s1 != s2");
	if(n != 1 + 2 * (strlen(s0) + strlen(z2)))
	    ERR("n should be 1 + 2 * (strlen(s0) + strlen(z2))");
	if(s1 != NULL && strncmp(s1, s0, strlen(s0)) != 0) {
	    ERRN("strncmp(s1, s0, strlen(s0)) should be 0");
	    printf("s1 = \\"%s\\", s0 = \\"%s\\"\\n", s1, s0);
	}
	if(s1 != NULL && strcmp(s1 + strlen(s0), z2) != 0) {
	    ERRN("strcmp(s1 + strlen(s0), z2) should be 0");
	    printf("s1+strlen(s0) = \\"%s\\", z2 = \\"%s\\"\\n", s1+strlen(s0), z2);
	}
	free(s1);
	TIDY;
    }
    return n_errs;
}

int test_explode_XX(int testN, const char * str, const char * delims)
{
    int n_errs = 0;
    int ind;
    int stulen, sollen;

    const char * indent = "   ";
    printf("\\ntest %0d :: explode(...)\\n\\n", testN);
    printf("%sconst char * str = \\"", indent);
    print_packed(str);
    printf("\\";\\n");
    printf("%sconst char * delims = \\"", indent);
    print_packed(delims);
    printf("\\";\\n");
    printf("%sint n;\\n", indent);
    printf("%schar * * strArr = explode(std, delims, &n);\\n", indent);

    char * * sol = explode_sol(str, delims, &sollen);
    char * * stu = explode(str, delims, &stulen);

    if(stulen != sollen) {
	printf("%s// Error, n = %d, but expected %d\\n", indent, stulen, sollen);
	n_errs++;
    } else {
	for(ind = 0; ind < stulen; ++ind) 
	    if(strcmp(stu[ind], sol[ind]) != 0)
		n_errs++;
    }

    if(n_errs == 0) {
	for(ind = 0; ind < stulen; ++ind) {
	    printf("%s// strArr[%d] is \\"", indent, ind);
	    print_packed(stu[ind]);
	    printf("\\"\\n");
	}
	printf("%s(pass.)\\n", indent);
    } else {
	printf("%sTestcase FAILED. Printing Solution:\\n", indent);
	int maxlen = sollen > stulen ? sollen : stulen;
	for(ind = 0; ind < maxlen; ++ind) {
	    if(ind < stulen && ind < sollen) {
		int match = strcmp(stu[ind], sol[ind]);
		if(match == 0)
		    printf("%sstrArr[%d] = \\"%s\\". (correct.)\\n", 
			   indent, ind, stu[ind]);
		else
		    printf("%sstrArr[%d] = \\"%s\\". Should be \\"%s\\"\\n",
			   indent, ind, stu[ind], sol[ind]);
	    } else if (ind < stulen) {
		printf("%sstrArr[%d] = \\"%s\\"; however, the solution has no such index\\n",
		       indent, ind, stu[ind]);
	    } else {
		printf("%sstrArr has no index %d; however, the %dth element should be \\"%s\\"\\n",
		       indent, ind, ind, sol[ind]);
	    }
	}
    }

    destroyStringArray_sol(stu, stulen);
    destroyStringArray_sol(sol, sollen);

    return n_errs;
}

int test_implode_XX(int testN, 
		    const char * str, 
		    const char * delims, 
		    const char * glue)
{
    int n_errs = 0;
    int ind;

    const char * indent = "   ";

    int len;
    char * * arr = explode_sol(str, delims, &len);

    printf("\\ntest %0d :: implode(...)\\n\\n", testN);
    printf("%sint len = %d\\n", indent, len);
    printf("%schar * * strArr = malloc(len * sizeof(char*));\\n", indent);
    for(ind = 0; ind < len; ++ind) {
	printf("%sstrArr[%d] = strdup(\\"", indent, ind);
	print_packed(arr[ind]);
	printf("\\");\\n");
    }
    printf("%sconst char * glue = \\"", indent);
    print_packed(glue);
    printf("\\";\\n");
    printf("%schar * s = implode(strArr, len, glue);\\n", indent);

    char * arr_bak = malloc(len * sizeof(char *));
    memcpy(arr_bak, arr, len * sizeof(char *));
    char * sol = implode_sol(arr, len, glue);
    char * stu = implode(arr, len, glue);

    printf("%s// s is \\"", indent);
    print_packed(stu);
    printf("\\"\\n");

    int mcmp = memcmp(arr_bak, arr, len * sizeof(char *));
    int cmp = strcmp(stu, sol);
    if(cmp == 0 && mcmp == 0) {
	printf("%s(pass.)\\n", indent);
    } else {
	n_errs++;
	printf("%sFAIL\\n", indent);
	if(mcmp != 0) { 
	    printf("%s// The memory in strArr has been corrupted!\\n", indent);
	}
	if(cmp != 0) {
	    printf("%s// expected: \\"", indent);
		print_packed(sol);
		printf("\\"\\n");
	}
    }

    destroyStringArray_sol(arr, len);
    free(stu);
    free(sol);
    free(arr_bak);
    return n_errs;
}

int test_sortStringArray_XX(int testN, const char * str, const char * delims)
{
    int n_errs = 0;
    int ind;

    const char * indent = "   ";

    int len1, len2;
    char * * arr1 = explode_sol(str, delims, &len1);
    char * * arr2 = explode_sol(str, delims, &len2);

    printf("\\ntest %0d :: sortStringArray(...)\\n\\n", testN);
    printf("%sint len = %d\\n", indent, len1);
    printf("%schar * * strArr = malloc(len * sizeof(char*));\\n", indent);
    for(ind = 0; ind < len1; ++ind) {
	printf("%sstrArr[%d] = strdup(\\"", indent, ind);
	print_packed(arr1[ind]);
	printf("\\");\\n");
    }
    printf("%ssortStringArray(strArr, len);\\n", indent);

    sortStringArray_sol(arr2, len2);
    sortStringArray(arr1, len1);
    
    for(ind = 0; ind < len1; ++ind) {
	printf("%s// strArr[%d] is \\"", indent, ind);
	print_packed(arr1[ind]);
	printf("\\"");
	if(strcmp(arr1[ind], arr2[ind]) != 0) {
	    n_errs++;
	    printf(", ERROR, expected \\"");
	    print_packed(arr2[ind]);
	    printf("\\"");
	}
	printf("\\n");

    }
    if(n_errs == 0)
	printf("%s(pass.)\\n", indent);
    else
	printf("%sFAIL\\n", indent);

    destroyStringArray_sol(arr1, len1);
    destroyStringArray_sol(arr2, len2);

    return n_errs;
}

int test_sortStringCharacters(int testN, const char * str)
{
    int n_errs = 0;
    const char * indent = "   ";

    char * s1 = strdup(str);
    char * s2 = strdup(str);

    printf("\\ntest %0d :: sortStringCharacters(...)\\n\\n", testN);
    printf("%schar * s1 = strdup(\\"", indent);
    print_packed(str);
    printf("\\");\\n");
    printf("%ssortStringCharacters(s1)\\n", indent);

    sortStringCharacters_sol(s2);
    sortStringCharacters(s1);

    printf("%s// s1 is now \\"", indent);
    print_packed(s1);
    printf("\\"");
    if(strcmp(s1, s2) != 0) {
	n_errs++;
	printf(", ERROR, expected \\"");
	print_packed(s2);
	printf("\\"");
    } 
    printf("\\n");

    free(s1);
    free(s2);

    return n_errs;
}

int test_destroyStringArray_XX(int testN, const char * str, const char * delims)
{
    int n_errs = 0;
    int ind;

    const char * indent = "   ";
    printf("\\ntest %0d :: destroyStringArray(...)\\n\\n", testN);

    if(str == NULL) {
	printf("%sdestroyStringArray(NULL, 0);\\n", indent);     
	destroyStringArray(NULL, 0);
    } else {
	int len;
	char * * arr = explode_sol(str, delims, &len);
	printf("%sint len = %d\\n", indent, len);
	printf("%schar * * strArr = malloc(len * sizeof(char*));\\n", indent);
	for(ind = 0; ind < len; ++ind) {
	    printf("%sstrArr[%d] = strdup(\\"", indent, ind);
	    print_packed(arr[ind]);
	    printf("\\");\\n");
	}
	printf("%sdestroyStringArray(strArr, len);\\n", indent);
	destroyStringArray(arr, len);
    }
    printf("%s// Pass conditional on no memory errors\\n", indent);

    return n_errs;
}

// --------------------------------------------------------- main(...)

#define NTESTS 32

int main(int argc, char * * argv)
{    
    if(argc == 1) {
	printf("%d\\n", NTESTS);
	return EXIT_SUCCESS;
    }  

    int test_number = atoi(argv[1]);
    switch(test_number) {
    case 0: return test_01();
    case 1: return test_02();
    case 2: return test_03();
    case 3: return test_04();    
    case 4: return test_explode_XX(5, "The\\nTuring test", " \\n");
    case 5: return test_explode_XX(6, "lady beatle brew", " ");
    case 6: return test_explode_XX(7, "The\\nTuring test", "");
    case 7: return test_explode_XX(8, "The\\nTuring test", "\\n");
    case 8: return test_explode_XX(9, "The\\nTuring test", "Tt");
    case 9: return test_explode_XX(10, "", "Tt");
    case 10: return test_explode_XX(11, "", "");
    case 11: return test_explode_XX(12, z1, " ,;.");
    case 12: return test_explode_XX(13, z3, "\\n");
    case 13: return test_explode_XX(14, "aaaaa", "a");
    case 14: return test_implode_XX(15, "The\\nTuring test", " \\n", " ");
    case 15: return test_implode_XX(16, "The\\nTuring test", "\\n", "{newline}");
    case 16: return test_implode_XX(17, "The\\nTuring test", "Tt", "");
    case 17: return test_implode_XX(18, "", "Tt", "Z");
    case 18: return test_implode_XX(19, "", "", "");
    case 19: return test_implode_XX(20, z1, " ,;.", " -- ");
    case 20: return test_implode_XX(21, z3, "\\n", ";\\n");
    case 21: return test_implode_XX(22, "1a2a3a4a5a6", "a", ", ");
    case 22: return test_sortStringArray_XX(23, "lady beatle brew", " ");
    case 23: return test_sortStringArray_XX(24, "", "");
    case 24: return test_sortStringArray_XX(25, z3, "\\n");
    case 25: return test_sortStringCharacters(26, z1);
    case 26: return test_sortStringCharacters(27, z2);
    case 27: return test_sortStringCharacters(28, z3);
    case 28: return test_sortStringCharacters(29, "");
    case 29: return test_destroyStringArray_XX(30, "lady beatle brew", " ");
    case 30: return test_destroyStringArray_XX(31, "", "");
    case 31: return test_destroyStringArray_XX(32, NULL, " ");
    default:
	fprintf(stderr, "Internal error, this should never happend. "
		"Please report this error to the course professor."
		"\\n");
    }

    return EXIT_FAILURE;
}
ENDEOF
}


# If there are non-embedded files, we can check them by examining
# their MD5 codes.

for FILE in $FILES ; do
    ! [ -e $FILE ] \
	&& echo "Failed to find $PA03 file: '$FILE'." \
	&& echo "Make sure you are executing in the $PA03 directory," \
	&& echo "and that '$FILE' is in that directory." \
	&& echo "Aborting." \
	&& exit 1
done

TIMEOUT=60s
DELAY1=2
DELAY2=4
MILLIDEFINE=

QUICK=0
if [ "$TAS" = "DEFINE_QUICK_TESTER" ] ; then
    QUICK=1
else
    for TA in $TAS ; do
	[ "$USER" = "$TA" ] && QUICK=1
    done
fi
(( $QUICK == 1 )) && DELAY1=0.0001 && DELAY2=0.0001 && MILLIDEFINE="-DQUICKTESTS"

# This is the temporary file that we'll nuke when we're done...
TMPD=$(mktemp -d /tmp/.XXXXXX)
TMPF=$TMPD/n-failed

trap cleanup EXIT
cleanup()
{
    rm -rf $TMPD
}

AOUT=$TMPD/a.out

print_message()
{
    cat <<EOF    
   ---------------------------------------------------------------------------
   Welcome to the $PA03 testing program. This program takes a _long_ time
   to execute. There is a reason for this. You should not rely on this
   program to test your code as you go. Instead, you should think about
   what your code should be doing, and what inputs should produce what
   outputs for each of your functions.
   
        YOU SHOULD THEN TEST EVERY PIECE OF CODE AS YOU WRITE IT 
   
                                 AND 
   
                        FIX MISTAKES AS YOU GO.
   
   When you are convinced that you have the entire assignment 100%% correct,
   then you can use this testing program to test it. 
   
   This will give you your mark assuming that you submit it correctly, and 
   there are no other irregularities.
EOF

    I=0
    printf "   "
    while [ "$I" -lt "75" ] ; do
	/bin/sleep $DELAY1
	printf "-"
	I=$(expr $I + 1)
    done
    echo
}

# Compile here...

cp $FILE $TMPD/$(basename $FILE)
cd $TMPD

for F in $EMBED ; do
    echo_$(echo $F | sed 's,\.,_,g') > $F
done

! gcc -Wall -Wshadow -g $(basename $FILE) -c -o answer03.o 1>out 2>err \
    && cat out \
    && cat err 1>&2 \
    && echo "Your assignment failed to compile... this is a FAIL, aborting." \
    && exit 1
cat out
cat err 1>&2
(( $(cat out | grep warning | wc -l) > 0 )) \
    && echo "Compiler warning detected, this is a FAIL, aborting." \
    && exit 1

echo_test_c | gcc -xc -Wall -Wshadow -g $MILLIDEFINE - -c -o test.o
! [ -e test.o ] \
    && echo "FATAL internal problem, please report this to aaron@pageofswords.net." \
    && exit 1

! gcc test.o answer03.o -o $AOUT 1>out 2>err \
    && cat out \
    && cat err 1>&2 \
    && echo "Your assignment failed to link. Maybe you have a main(...) function" \
    && echo "in your '$FILE' file. Irrespective, this is a FAIL, aborting." \
    && exit 1

rm -f $TMPD/*.c

print_message

NTESTS=$($AOUT)
! [ "$NTESTS" -eq "$NTESTS" 2>/dev/null ] \
    && echo "FATAL internal problem, test's main(...) failed to disclose test cases." \
    && echo "Aborting." \
    && exit 1

printf "0" > $TMPF 
I=0
while (( $I < $NTESTS )) ; do
    timeout $TIMEOUT \
	valgrind --tool=memcheck --leak-check=full --verbose --log-file=memcheck.log \
	$AOUT $I
    RET=$?
    (( $RET == 124 )) && echo "Testcase timed out after $TIMEOUT, probably infinite loop."
    VAL_BAD=1
    cat memcheck.log | grep -q "ERROR SUMMARY: 0 errors from 0 contexts" && VAL_BAD=0
    (( $VAL_BAD == 1 )) \
	&& echo "Memory errors detected, testcase failed." \
	&& cat memcheck.log
    (( $VAL_BAD == 1 )) || (( $RET != 0 )) \
	&& N="$(cat $TMPF)" && printf "$(expr 1 + $N)" > $TMPF
    I=$(expr $I + 1)
    /bin/sleep $DELAY2
done

N="$(cat $TMPF)"
printf "\n\n%d/%d testcases passed.\n" "$(expr $NTESTS - $N)" "$NTESTS"

if (( $SUPPRESS_MARK == 0 )) ; then
    (( $N == 0 )) && echo "Overall mark is a PASS." && exit 0
    (( $N != 0 )) && echo "Overall mark is a FAIL." && exit 0
else
    echo "Please look up your mark on blackboard"
    (( $N == 0 )) && exit 0
    exit 1
fi
 
