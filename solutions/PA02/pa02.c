
#include <stdio.h>
//#include <string.h>

#include "answer02.h"

#define BUFFER_LEN 1024

int main(int argc, char * * argv)
{
    printf("Welcome to PA02.\n"
	   "\n"
	   "You are encouraged to edit this file in order to test\n"
	   "the behavior of the functions you write in answer02.c\n"
	   "\n"
	   "This file will not be marked, and should not be\n"
	   "submitted.\n"
	   "\n"
	   "Don't forget to post questions on blackboard, and ask\n"
	   "the TAs and your classmates for help.\n"
	   "\n");

    const char * s1 = "Hello World!";
    const char * s2 = "";
    const char * s3 = "foo";

    // -- my_strlen, should be: 12, 0, and 3
    printf("my_strlen(\"%s\") = %d\n", s1, (int) my_strlen(s1));
    printf("my_strlen(\"%s\") = %d\n", s2, (int) my_strlen(s2));
    printf("my_strlen(\"%s\") = %d\n", s3, (int) my_strlen(s3));

    // -- my_countchar, should be: 3, 0, and 2
    printf("my_countchar(\"%s\", 'l') = %d\n", s1, (int) my_countchar(s1, 'l'));
    printf("my_countchar(\"%s\", 'o') = %d\n", s2, (int) my_countchar(s2, 'o'));
    printf("my_countchar(\"%s\", 'o') = %d\n", s3, (int) my_countchar(s3, 'o'));

    // -- my_strchr, should be: "llo World!", "(null)", and ""
    printf("my_strchr(\"%s\", 'l') = %s\n", s1, my_strchr(s1, 'l'));
    printf("my_strchr(\"%s\", 'o') = %s\n", s2, my_strchr(s2, 'o'));
    printf("my_strchr(\"%s\", '\\0') = %s\n", s3, my_strchr(s3, '\0'));
    
    // -- my_strrchr, should be "orld!", "null" and  ""
    printf("my_strrchr(\"%s\", 'l') = %s\n", s1, my_strrchr(s1, 'l'));
    printf("my_strrchr(\"%s\", 'o') = %s\n", s2, my_strrchr(s2, 'o'));
    printf("my_strrchr(\"%s\", '\\0') = %s\n", s3, my_strrchr(s3, '\0'));

    // -- my_strstr, should be: "World!", "Hello World!", "(null)"
    printf("my_strstr(\"%s\", \"World\") = %s\n", s1, my_strstr(s1, "World"));
    printf("my_strstr(\"%s\", \"\") = %s\n", s1, my_strstr(s1, ""));
    printf("my_strstr(\"%s\", \"hello\") = %s\n", s1, my_strstr(s1, "hello"));

    // -- my_strcpy. For this function you need a buffer where you
    // copy the string to. 
    char buffer[BUFFER_LEN];
    my_strcpy(buffer, s1);
    printf("my_strcpy(buffer, \"%s\"), buffer = \"%s\"\n", s1, buffer);
    my_strcpy(buffer, s2);
    printf("my_strcpy(buffer, \"%s\"), buffer = \"%s\"\n", s2, buffer);
    my_strcpy(buffer, s3);
    printf("my_strcpy(buffer, \"%s\"), buffer = \"%s\"\n", s3, buffer);

    // -- my_strcat. You will have to do this yourself... just
    // look at my_strcpy for an example, and go from there.
    const char * string = "Hello";
    const char * st1 = "Zello!";
    const char * st2 = " ";
    my_strcpy(buffer, string); 
    my_strcat(buffer, st1);
    printf("my_strcat(buffer, \"%s\"), buffer = \"%s\"\n", st1, buffer);
    my_strcat(buffer, st2);
    printf("my_strcat(buffer, \"%s\"), buffer = \"%s\"\n", st2, buffer);

    // -- my_isspace. You will have to do this for yourself.
    int space;
    space = my_isspace(' '); 
    printf("my_isspace(' '), return value is \"%i\"\n", space);
    space = my_isspace('\f');
    printf("my_isspace('/f'), return value is \"%i\"\n", space);
    space = my_isspace('\n');
    printf("my_isspace('/n'), return value is \"%i\"\n", space);
    space = my_isspace('\r');
    printf("my_isspace('/r'), return value is \"%i\"\n", space);
    space = my_isspace('\t');
    printf("my_isspace('/t'), return value is \"%i\"\n", space);
    space = my_isspace('\v');
    printf("my_isspace('/v'), return value is \"%i\"\n", space);
    space = my_isspace('A');
    printf("my_isspace('A'), return value is \"%i\"\n", space);

    // -- my_atoi. You will have to do this for yourself.
    int myatoi;
    myatoi = my_atoi("0");
    printf("yo man");
    printf("my_atoi(0), return value is \"%i\"\n", myatoi);
    myatoi =  my_atoi("-12");
    printf("my_atoi(-12), return value is \"%i\"\n", myatoi);
    myatoi =  my_atoi("15th of March would be the ides.");
    printf("my_atoi(15th of March would be the ides.), return value is \"%i\"\n", myatoi);
    myatoi =  my_atoi("4 months to Summer.");
    printf("my_atoi(4 months to Summer.), return value is \"%i\"\n", myatoi);
    myatoi =  my_atoi("\n\f\t\v\r 6 white");
    printf("my_atoi(/n/f/t/v/r 6 white), return value is \"%i\"\n", myatoi);
    myatoi = my_atoi("garbage");
    printf("my_atoi(garbage), return value is \"%i\"\n", myatoi);


    return EXIT_SUCCESS;
}


