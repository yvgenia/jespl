#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include "font.h"

void prsym(int idx) {
	int iline;
	char *(*symbol)[SYMBOL_HEIGHT] = &alphabet[idx];
	for(iline = 0; iline!=SYMBOL_HEIGHT; ++iline){
	      printf("%s\n", (*symbol)[iline]);

	}
	  
	    
}


int length(char* str){
  return strlen(str);
}

void print(char* s){
  printf("%s", s);
}

int bigger(int ch,int x){
  return (ch-x>=0);
}

int smaller(int ch,int x){
  return ((x-ch)>=0);
}

int check(int ch){
  int ans1= bigger(ch,128);
  int ans2= smaller(ch,154);
  return (ans1 && ans2);
}

int change(int ch,int d){
  return (ch-d);
}

void printW(char* word, int iline){
    int index, len, j;
    len = length(word);
    for (j=0; j<len; j++){
	if(check(word[j])){
	  index = change(word[j],17);
	}
	else{
	  index = change(word[j],32);
	}
	char *(*symbol)[SYMBOL_HEIGHT] = &alphabet[index]; //index - the index of a certain character in the vertical array
	print((*symbol)[iline]); //prints the suitable line (part of the character)
    }
    char *(*symbol)[SYMBOL_HEIGHT] = &alphabet[0]; //space
    print((*symbol)[iline]);
}


int main(int argc, char **argv) {
	int i, iline;
	  //each argument in argv is one word

	for(iline = 0; iline!=SYMBOL_HEIGHT; ++iline){
		for (i=1; i<argc; i++){
			printW(argv[i],iline);
		}
		printf("\n");
	}
	
	return 0;
}
