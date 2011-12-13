#include <stdio.h>

/* invert the words in sentence */
 int main(int argc, char **argv) {
   int i;
   
   printf("The reverse phrase is: '");

   for(i=argc-1; i>=1; --i) {
      printf("%s", argv[i]);
      if(i!=1)
        printf(" ");
   }
   
   printf("'.\n");

   return 0;
 }
