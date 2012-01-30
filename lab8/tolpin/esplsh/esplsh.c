#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <sys/stat.h>
#include <fcntl.h>
 

#define BUF_LEN 1024
static char command[BUF_LEN+1];
static int argc;
static char *argv[BUF_LEN+1];

/* read command and remove end of line if present */
int read_command() {
  int len;

  if(fgets(command, BUF_LEN, stdin)) {
    len = strlen(command);
    if(len>0 && command[len-1]=='\n')
      command[len-1] = '\0';
    return 1;
  } 
  
  return 0;
}

#define NO_SEP '\0'
#define EOC '\1'

/* split the command line into arguments and fill argv with pointers
   to the arguments */
void split_command() {
  char *s, sep;
  int between;

  between = 1;
  argc = 0;
  sep = NO_SEP;
  for(s = command; *s; ++s) {
    switch(*s) {
    case '\"': case '\'':
      if(sep==NO_SEP) {
        sep = *s;
      } else if(sep==*s) {
        sep = '\0';
      } 
      break;
    case '\\':
      ++s;
      break;
    case ' ':
      if(!sep) {
        between = 1;
        *s = '\0';
        continue;
      }
      break;
    }
    if(between) {
      argv[argc++] = s;
      between = 0;
    }
  }
  argv[argc] = NULL;
}

/* expand arguments, substitute shell variable values etc. */
void expand_args() {
  char **a = argv;
  while(*a) {
    if(**a=='"' || **a=='\'') { /* TODO: quotes can be in any place */
      *a = strdup(*a);
      memmove(*a, *a+1, strlen(*a));
      (*a)[strlen(*a)-1] = 0;
    } else {
      *a = strdup(*a);
    }
    /* TODO: eliminate escapes \ */
    /* TODO: expand environment variables */
    ++a;
  }
}

/* free arguments allocated during expansion */
void free_args() {
  char **a = argv;
  while(*a) {
    free(*a);
    ++a;
  }
}

/* run an external program */
void run_program() {
	int fd,fd2, pid, status;
	int cfd[2], cpid, cstatus;
	static char ststr[8];
	int i;
	int pipeidx=-1;
	

	for (i=1; i<argc; ++i){
		if (!strcmp(argv[i],"|"))
			pipeidx= i;
	}
fprintf(stdout,"pipeidx: %d \n", pipeidx);

	if (pipeidx>-1){
  	    pipe(cfd); 
	}

	/* TODO: background commands */
	pid=fork();

	if(pid==0) {		// first child

	    /*input, output redirection */
	    if(argc>2) {
		if (!strcmp(argv[argc-2],">")){     //output
		    fd= open(argv[argc-1], O_WRONLY|O_TRUNC|O_CREAT, 0644);
		    if(fd<0)
		      perror(argv[argc-1]);
		    fd2 = dup2(fd,1);
		    argv[argc-2]=0;
		} else if (!strcmp(argv[argc-2],"<")){
		    fd= open(argv[argc-1],O_RDONLY);
		    dup2(fd,0);
		    argv[argc-2]=0;
		}
	    }
	    if(pipeidx>-1){
		argv[pipeidx]=0;
		close(cfd[0]); //close the reading end
		dup2(cfd[1], 1); //this child will write to the pipe
	    }
	    execvp(argv[0], argv);
	    perror(argv[0]);
	
	}
	else if (pid>0){	// parent	
		    /* pipelines */
		            
	           if((cpid = fork()) == -1){
	                perror("fork");
	           }
	           if(cpid == 0) {			// second child
			  close(cfd[1]);
		  	  dup2(cfd[0], 0);
 	                execvp(argv[pipeidx+1],argv+pipeidx+1);
	 		  perror(argv[pipeidx+1]);
	           }
		    else if (cpid > 0){		// there was a pipe
			  close(cfd[0]);
              	  close(cfd[1]);
			  waitpid(pid,&status,0);
	                waitpid(cpid,&cstatus,0);
		   	  sprintf(ststr, "%d", status);
			  setenv("?", ststr, 1);	  
	           }
		    else{		// no pipe
 			  waitpid(pid, &status, 0);
			  sprintf(ststr, "%d", status);
			  setenv("?", ststr, 1);
		    }
	}	
	else {
		perror(getenv("SHELL")); /* problem while forking, not due to a particular program */
   	}
}    // run program

int main(int _argc, char **_argv) {
  /* clear shell variables and  re-assign a minimum set */
  clearenv();
  setenv("PATH", ":/bin:/usr/bin", 1);
  setenv("PROMPT", "$ ", 1);
  setenv("SHELL", _argv[0], 1);

  signal(SIGINT, SIG_IGN); /* ignore ^C */

  while(1) {
    printf("%s", getenv("PROMPT"));
    if(!read_command())
      break;
    split_command();
    if(!argc)
      continue;
    expand_args();
    /* process builtin commands */
    if(!strcmp(argv[0],"exit")) {
      break;
    } else if(!strcmp(argv[0],"set")) {
      if(argc!=3) {
        fprintf(stderr, "set: two arguments required\n");
        continue;
      }
      setenv(argv[1], argv[2], 1);
    } else if(!strcmp(argv[0], "cd")) {
      if(argc!=2) {
        fprintf(stderr, "cd: one argument required\n");
        continue;
      }
      if(chdir(argv[1])==-1) {
        perror("cd");
      }
    } else if(!strcmp(argv[0], "pwd")) {
      if(argc!=1) {
        fprintf(stderr, "pwd: no arguments allowed\n");
        continue;
      }
      printf("%s\n", getcwd(command, BUF_LEN));
    } else {
      /* run external command */
      run_program();
    }
    free_args();
  }
  printf("\n");

  return 0;
}
    

    
