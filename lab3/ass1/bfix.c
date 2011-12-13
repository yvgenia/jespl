#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "diff.h"

#define BUFSIZE 128


int main(int argc, char **argv) {
  
	int hvalue=0;
	int rvalue=0;  
	int mvalue=0;
	int c;
	
	while ((c = getopt(argc, argv, "hrm")) != -1) {
		switch (c) {
		    case 'h':
		        hvalue=1;
			break;
		    case 'r':
		        rvalue=1;
			break;
		    case 'm':
		        mvalue=1;
			break;
		    case '?':
			if (isprint (optopt))
			  fprintf (stderr, "Unknown option `-%c'.\n", optopt);
			else
			  fprintf (stderr,"Unknown option character `\\x%x'.\n",optopt);
		    default:
			abort ();
		}
	}
	    
	if (hvalue){
		printf("bfix.c options are:\n-h  print a summary of options and exit\n-r  reverse the differences\n-m  print a message each time a change is applied\n");
	}
	else{
		if(argc != 3) {
		      printf("please run this program with two arguments.\n");
		}
		else{
			FILE *fchange , *filediff;
			char diffline[BUFSIZE];
			char found,old,new;
			if ( (fchange = fopen(argv[1],"r+")) == NULL)
				printf ("file %s couldn't be opened\n",argv[1]);
			if ( (filediff = fopen(argv[2],"r")) == NULL)
				printf ("file %s couldn't be opened\n",argv[2]);
			else{
				for(;;) {
					if(feof(filediff))
					      break;
					
					fgets(diffline,BUFSIZE,filediff);		// get line from difference file
					
					struct diff diff; 				// parse the line
					parsediff(diffline,&diff);
					
					fseek(fchange,diff.offset-1,SEEK_SET);		// move to offset
					fread(&found,1,1,fchange);			// read the byte existing in the file
					fseek(fchange,diff.offset-1,SEEK_SET);		// move back one byte
					
					
					if (rvalue){					// process the -r option
					      old= diff.new;
					      new= diff.old;
					}
					else{
					      old= diff.old;
					      new= diff.new;
					}
					
					
					if (found==old){				// change the value
					      fwrite(&new,1,1,fchange);
					}
					else{
					      printf ("couldn't find the old byte\n");
					}
					
					printf ("diff.offset: %ld, old: %c, new: %c, found: %c\n",(diff.offset),old,new,found);					
				}
			}
		}
	}
	return 0;	      
}
