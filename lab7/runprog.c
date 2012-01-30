#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  int i;
  pid_t pid;
  int status;
  for (i=1; i<argc; ++i){
      printf("%s ",argv[i]);
  }
  printf("\n");
  
  pid = fork();
  if (pid == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
  }
  if (pid){
      wait(&status);
      printf("exit status: %d\n", WEXITSTATUS(status));
  } else {
      execvp(argv[1],argv+1);
      exit(255);
  }
  
return 0;
}
