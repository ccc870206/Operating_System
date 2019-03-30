#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main()
{

    
    char input[1000];
    char *command;
    char *command2;
    char *arg[100];
    char *arg2[100];
   
    
while(printf(">"))
{
    int flag = 1;
    int tag = 0;
    gets(input);

    char *space = " ";
    char *ss;
    
    arg2[0] = NULL;

    ss = strtok(input,space);

    command = ss;


    int i = 0;

    while(ss!=NULL)
    {
        if(tag)
        {
            arg2[i] = ss;
            
	    i++;
	    ss = strtok(NULL,space);
        }
	else
	{
            if(!strcmp(ss,"&"))
	    {
	          
               flag = 0;
               break;
	    }
	    if(!strcmp(ss,"|"))
	    {
	        arg[i] = NULL;
	        i = 1;
	        tag = 1;
	        flag = 2;	        
	        ss = strtok(NULL,space);
	        command2 = ss;
	        arg2[0] = command2;
	        ss = strtok(NULL,space);
	        continue;
	    }
	    if(!strcmp(ss,">"))
	    {
	        arg[i] = NULL;
	        flag = 3;	        
	        ss = strtok(NULL,space);
	        command2 = ss;
	      
	        break;
	    }
	    
            arg[i] = ss;
           
            i++;
            ss = strtok(NULL,space);
        }
    }
    
    if(tag)
    {
        arg2[i]=NULL;
    }
    else
        arg[i]=NULL;

    int j = 0;

        

    pid_t pid = fork();

    if(pid < 0)
    {
        fprintf(stderr,"Fork Failed\n");
        exit(-1);
    }
    else if(pid == 0)
    {
      
        if(flag == 1)
        {            
            execvp(command,arg);
            printf("The command is failed\n");
        }
        else if(flag == 0)
        {   
            if(fork() < 0)
                fprintf(stderr,"Fork Failed\n");
            else if(fork()==0)
            {             
                execvp(command,arg);
                printf("The command is failed\n");
            }
                
            else
            {
                exit(0);    
            }    
        }
        else if(flag == 2)
        {
            int fd[2];
            pipe(fd);
            pid_t pid2 = fork();
           
            if(pid2<0)
            {
                fprintf(stderr,"Fork Failed\n");
                exit(-1);
            }                
            else if(pid2==0)
            {
            
                close(fd[0]);
               
                dup2(fd[1],1);
              
                close(fd[1]);
                             
                execvp(command,arg);
                printf("FAILED GRANDSON\n");
            }       
            else
            {
                
                wait(NULL);
                
                dup2(fd[0],0);
                close(fd[0]);
                
                execvp(command2,arg2);
                printf("FAILED CHILED\n");          
            }
        }
        else if(flag == 3)
        {
            int fd[2];
            pipe(fd);
                       
            fd[1] = creat(command2,0);
            dup2(fd[1],1);
            close(fd[1]);
            
            dup2(fd[0],0);
            close(fd[0]);
            
            execvp(command,arg);
            printf("FAILED CHILED\n");  
        }
    }
    else
    {
        wait(NULL);
    }

}

    return 0;
}



