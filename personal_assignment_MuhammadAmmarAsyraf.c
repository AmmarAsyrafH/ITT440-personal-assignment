#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>



void sighandler(int sig) 
{
   printf("Process interrupted\n");
   exit(1);
}
int main()
{
	
    	int pipe1[2]; 
    	int pipe2[2];
    	
    	char name[100];
    	char message[100];
        	
    	signal(SIGINT, sighandler);
    
        
        	if (pipe(pipe1) == -1) 
          	{
        		perror("Pipe 1 Failed");
        		return 0;
        	}
        
        	else if (pipe(pipe2) == -1)
        	{
        	    perror("Pipe 2 Failed");
        	    return 0;
        	}
            
        	pid_t pid1 = fork();
        	
        	
        	if (pid1 > 0) 
          	{
			printf("Enter Name: \n");
			scanf("%s", name); 
			printf("\n Write a message (not exceed 3 words) \n");
			scanf(" %[^\n]s" ,message);
			write(pipe1[1], name,100);
			write(pipe2[1], message,100);
			close(pipe1[1]);
			close(pipe2[1]);
			wait(NULL);
        	}
        	
        	if (pid1 == 0 )
        	{
        		close(pipe1[1]);
        		read(pipe1[0], name,100);
        		printf("Your Name: %s \n", name);
        		close(pipe1[0]);
        	}
        	else if (pid1 > 0)
        	{
        		close(pipe2[1]);
        		read(pipe2[0], message, 100);
        		printf("Message: %s \n", message);
        		close(pipe2[0]);
        		
        	}
        
        	return 0;
        
	
}
