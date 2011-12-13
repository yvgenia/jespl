#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "namelist.h"

#define BUFLEN 128

typedef int(*funcptr)(const void*,const void*);

int find_word(char** arr, char* w){
	int i=0;
	while (arr[i]){
	     if (!strcmp(arr[i],w))
		  return 1;
	     ++i;
	}
	return 0;
}

void print_words(namelist nl){
	int i;
	for(i = 0; i!=nl->size; ++i) {
		printf("%s %d\n", nl->names[i].name, nl->names[i].count);
	}
}

int sort_namestat(struct namestat* n1,struct namestat* n2){
	return strcmp(n1->name,n2->name);
}

void sort_words(namelist nl){
	qsort((void*)nl->names, nl->size, sizeof(struct namestat), (funcptr) sort_namestat);
}



int main(int argc, char **argv) {
	if(argc == 1) {
		printf("please run this program with at least one argument.\n");
	}
	else{
		int i;
		char buffer[BUFLEN];
		char* saved_words[]= {"int","char","if","else","while","for","return",(char*)0};
		namelist file_words= make_namelist();
		for (i=1; i<argc; ++i){
		      FILE *fptr;
		      if ( (fptr = fopen(argv[i],"r")) == NULL)
			    printf ("file %s couldn't be opened\n",argv[i]);
		      else {
			    char word[BUFLEN];
			    int ich = 0;
			    int isaved = 0;
			    int inword = 0;
			    for(;;) {
				int ch = fgetc(fptr);
				if(feof(fptr))
				      break;
				if(inword) {
				      if(isalpha(ch)) {    // adding char to the word
					  word[ich] = ch;
					  ++ich;
				      } 
				      else{     // just finished reading a word
					  word[ich] = 0;
					  ich = 0;
					  inword = 0;
					  if (!find_word(saved_words,word)){
						add_name(file_words,word);
					  }
	
				      }
				}
		
				else {
				      if(isalpha(ch)) {        //for the first char of the word
					  ungetc(ch,fptr);
					  inword=1;
				      } 
				      if (ch == '\"'){
					  ch = fgetc(fptr);
					  while (ch != '\"')
						ch = fgetc(fptr);
				      }
				}
			    }
		      }
		}
		sort_words(file_words);
		print_words(file_words);
	}
	return 0;
}