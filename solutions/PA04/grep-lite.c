#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


const char * const helpmsg [] = {"\nUsage: grep-lite [OPTION]... PATTERN\n" 
	"Search for PATTERN in standard input. PATTERN is a\n"
	"string. grep-lite will search standard input line by\n"
	"line, and (by default) print out those lines which\n"
	"contain pattern as a substring.\n\n"

	"  -v, --invert-match     print non-matching lines\n"
	"  -n, --line-number      print line numbers with output\n"
	"  -q, --quiet            suppress all output\n\n"

	"Exit status is 0 if any line is selected, 1 otherwise;\n"
	"if any error occurs, then the exit status is 2.\n\n"};


int main(int argc, char * * argv) {	
	bool flagv = false;
	bool flagn = false;
	char * pattern;
	char buffer[2000];
	int line = 1;
	int i;
	int counter = 0;
	//1. return error msg if there's no arg
	//and return 2 as an error occurs
	if ( argc == 1 ) {
		fprintf(stderr, "Invalid input (missing argvs). \nPlease type [--help] to see the instructions.\n");
		return 2;
	}

	//check every position in argv
	//2.print helpmsg and exit_success on hitting "--help"
	for (i = 1; i < argc; i ++) {
		if ( strcmp(argv[i], "--help") == 0 ) {
			printf ("%s", *helpmsg);
			return EXIT_SUCCESS;
		}
	}
	//3. check for pattern
	if ( (*argv[argc - 1] == '-')) {
		fprintf(stderr, "Invalid input (missing PATTERN).\nPlease type [--help] to see the instructions.\n");
		return 2;
	}
	else pattern = argv[argc - 1];

	//4. check options	
	for (i = 1; i < argc - 1; i ++) {
		//	 invert match, set the flag of v 
		flagv = flagv || (strcmp(argv[i], "-v") == 0) || (strcmp(argv[i], "--invert-match") == 0) ;
		//	 line number, set the flag of n 
		flagn = flagn || (strcmp(argv[i], "-n") == 0) || (strcmp(argv[i], "--line-number") == 0) ;
		//   quiet
		if ( (strcmp(argv[i], "-q") == 0) || strcmp(argv[i], "--quiet")  == 0 ) {
			return EXIT_SUCCESS;
		}
		//   anyother bogus argvs
		if ( (!flagv) && (!flagn) ) {
			fprintf(stderr, "Invalid input (bogus argvs). \nPlease type [--help] to see the instructions.\n");
			return 0;
		}
	}
	
	//print the content
	while ( fgets(buffer, 2000, stdin) != NULL ) {
		//current line does NOT contain the pattern
		if ( (strstr(buffer, pattern) == NULL) ) {
			// if the inverse-match flag is set, print out current line
			if (flagv) {
				if (flagn) printf("%d:%s", line, buffer);
				else printf ("%s", buffer);
				counter ++;
			}	
			// else nothing
		}

		//current line contains the pattern
		if ( (strstr(buffer, pattern) != NULL) ) {
			// if the inverse-match flag is NOT set, print out current line
			if ( !(flagv) ) {
				if (flagn) printf("%d:%s", line, buffer);
				else printf ("%s", buffer);
				counter ++;
			}
			// else nothing
		}
		line ++;
	}
	return (counter == 0);
}


