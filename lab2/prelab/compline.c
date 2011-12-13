#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
	char buffer_f[500];
	char buffer_s[500];
	int i=1;
	if(argc != 3) {
		printf("please run this program with two arguments.\n");
	}
	else{
		FILE *first , *second;
		if ( (first = fopen(argv[1],"r")) == NULL)
			printf ("file %s couldn't be opened\n",argv[1]);
		if ( (second = fopen(argv[2],"r")) == NULL)
			printf ("file %s couldn't be opened\n",argv[2]);
		else
			while (!feof(first)){
				char* line_f= fgets(buffer_f, 500, first);
				char* line_s= fgets(buffer_s, 500, second); 
				if(strcmp(line_f,line_s) != 0){
					printf("-%d: %s",i,line_f);
					printf("+%d: %s",i,line_s);
				}
				++i;
			}
	}
	return 0;
}
