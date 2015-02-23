#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int compare(const void * p1, const void * p2){
    const char * a = (const char *) p1;
    const char * b = (const char *) p2;
    printf("this is a: %c (%p)\n", *a, a);
    printf("this is b: %c (%p)\n", *b, b);
    return (*a - *b);
}

int main(int argc, char * * argv) {
    printf("\nTesting sortStringchar(...)\n");
    char * strArr = (char*)malloc (100);
    strcpy(strArr, "fiiwrng9f9235o45yjnsdmjg 3D@3g ER #$RY( TG SDF g e");
   
    printf("%s\n", strArr);
    
    qsort(strArr, strlen(strArr), sizeof(char), compare);

    printf("After sort, we have:\n");
    printf("%s\n", strArr);

    return EXIT_SUCCESS;
}

