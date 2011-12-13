#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "font.h"

void arrsym(char** arr, int col, int idx) {
	int iline;
	char *(*symbol)[SYMBOL_HEIGHT] = &alphabet[idx];
	for(iline = 0; iline!=SYMBOL_HEIGHT; ++iline){
		arr[iline*strlen((*symbol)[iline])+col]= (*symbol)[iline];
	}
}

void prsym(int idx) {
	int iline;
	char *(*symbol)[SYMBOL_HEIGHT] = &alphabet[idx];
	for(iline = 0; iline!=SYMBOL_HEIGHT; ++iline){
		printf("%s\n", (*symbol)[iline]);
	}
}

int main(int argc, char **argv) {
	int i,j,k,p,idx;
	if(argc==1) {
			for(idx = 0;; ++idx) {
				if(!alphabet[idx][0])
					break;
				prsym(idx);
			}
	}
	else{
	   if (argc>1) {
		  for(i=1; i<argc; ++i) {
		    j=0;
   	           char *arra[SYMBOL_HEIGHT][strlen(argv[i])];
		    while (argv[i][j] != 0){
			idx= argv[i][j];
			if (((idx>=65) && (idx<=90)) || ((idx>=97) && (idx<=122))){
			    arrsym(arra,j,idx-32);
			}
			++j;
		    }
		    for (k=0; k<SYMBOL_HEIGHT; ++k){
			for (p=0; p<strlen(argv[i]); ++p)
				printf("%s ",arra[k][p]);
			printf("\n");
		    }
		  } 
	   }
	   else{
		printf("print all available symbols or a symbol by the given index in ASCII art.\n\nusage: %s [symbol-index]\n", argv[0]);
		return 1;
	   }
	}
	return 0;
}
