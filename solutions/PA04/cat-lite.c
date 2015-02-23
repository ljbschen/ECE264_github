#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char * const helpmsg [] = {"\nUsage: cat-lite [--help] [FILE]... \n"  
"With no FILE, or when FILE is -, read standard input.\n\n"  
"Examples:\n" 
" cat-lite README   Print the file README to standard output.\n" 
" cat-lite f - g    Print f's contents, then standard input, \n" 
"                   then g's contents.\n" 
" cat-lite          Copy standard input to standard output.\n\n"};

int main(int argc, char * * argv) {
	FILE * fp;
	char c;
	
	//print standard input on no argv
	if ( argc == 1 ) {
		while ( (c = fgetc(stdin)) != '\n' ){
			fputc(c, stdout);
			fflush(stdout);
		}
		printf("\n");
		return EXIT_SUCCESS;
	}

	//check every position in argv
	//print helpmsg and exit_success on hitting "--help"
	int i;
	for (i = 1; i < argc; i ++){
		if (strcmp(argv[i], "--help") == 0 ) {
			printf ("%s", *helpmsg);
			return EXIT_SUCCESS;
		}
	}

	//otherwise read each argv as file name
	//open each file in turn and print to stdout
	for (i = 1; i < argc; i ++){
		//print standard input on hitting "-"
		if ( strcmp(argv[i], "-") == 0 ) {
			while ( (c = fgetc(stdin)) != '\n' ){
				fputc(c, stdout);
				fflush(stdout);
			}
			printf("\n");
			i++;
			if (i == argc) return EXIT_SUCCESS;
		}
		
		//print out content on normal files
		if ( (fp = fopen(argv[i], "r")) ) {
			while ( (c = fgetc(fp)) != EOF ) {
				fputc(c, stdout);
				fflush(stdout);
			}
			fclose (fp);
		}

		//print error msg and return failure
		else {
			fprintf(stderr, "cat cannot open %s\n", argv[i]);
			return EXIT_FAILURE;
		}

		printf("\n");

	}

	return EXIT_SUCCESS;


}