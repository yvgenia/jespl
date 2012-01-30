#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {

        int     fd[2], nbytes;
        pid_t   childpid;
        char    string[];
        char    readbuffer[8000];

	 int i,j,k,newl;
	 int status;
	 int nflag=1;
	 int line =1;

	 if (!strcmp(argv[1],"-n")){
		nflag=2;
	 }
	 for (i=nflag; i<argc; ++i){
	      printf("%s ",argv[i]);
	 }
	 printf("\n");
  
	 pipe(fd);   
        
        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(EXIT_FAILURE);
        }

        if(childpid == 0)
        {
	  
		/* Child process closes up input side of pipe */
		close(fd[0]);

                /* Child process closes up stdout and copies fd[1] to 1 in the file discriptores array*/
  		dup2(fd[1], 1);
		

                execvp(argv[nflag],argv+nflag);

                /* Send "string" through the output side of pipe */
                //write(fd[1], string, (strlen(string)+1));

		exit(255);

        }
        else
        {
                /* Parent process closes up output side of pipe */
                close(fd[1]);

	        wait(&status);

                /*Read in a string from the pipe */
		j=1;
		while (nbytes = read(fd[0], readbuffer, sizeof(readbuffer))){
		    for (k=0; k<nbytes; ++k){
		      newl=1;
		      if (newl
		    }


	         printf("exit status: %d\n", WEXITSTATUS(status));
        }
        
        return(0);
}
