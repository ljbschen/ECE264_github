#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * * argv) {
	//printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", argv[0],argv[1],argv[2],argv[3],argv[4],argv[5],argv[6],argv[7],argv[8],argv[9]);
	//printf("%d\n", *argv[5]);
	int i;
	for (i = 1; i < argc; i++){
		if ((argv[i]) == " "){
			printf ("%s", argv[i]);
			while ((argv[i++]) == " ") ;
		}
		printf ("%s ", argv[i]);
	}
	printf("\n");
	return EXIT_SUCCESS;
}


