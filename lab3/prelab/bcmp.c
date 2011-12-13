#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
	int i=1;
	if(argc != 3) {
		printf("please run this program with two arguments.\n");
	}
	else{
		FILE *first , *second;
		char byte1[1], byte2[1];
		if ( (first = fopen(argv[1],"r")) == NULL)
			printf ("file %s couldn't be opened\n",argv[1]);
		if ( (second = fopen(argv[2],"r")) == NULL)
			printf ("file %s couldn't be opened\n",argv[2]);
		else{
			for(;;) {
				if(feof(first) && feof(second))
				      break;
				if (feof(first)){
					printf ("file %s is longer than file %s.\n",argv[2],argv[1]);
					break;	
				}
			  	if (feof(second)){
					printf ("file %s is longer than file %s.\n",argv[1],argv[2]);
					break;
				}
				fread(byte1,sizeof(char),1,first);
				fread(byte2,sizeof(char),1,second);
				if (byte1[0]!=byte2[0]){
					printf ("byte %d -%d +%d\n",i,byte1[0],byte2[0]);
				}
				++i;					
			}
		}
	}
	return 0;
}
