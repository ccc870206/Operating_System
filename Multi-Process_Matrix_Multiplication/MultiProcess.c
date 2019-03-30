#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Detach();
void Delete();

int* mc;

int main()
{
    struct timeval start,end;
    
    int n;
    printf("Input the matrix dimension:");
    scanf("%d",&n);
    
    int i,j,k;
    
    int num = 0;
    
    int* ma;
    int shm_id1;
    key_t key1;
    
    if((shm_id1 = shmget(key1,n*n*sizeof(int),IPC_CREAT|0666)) < 0)
    {
    	perror("shmget1");
    	return 0;
    }
    if((ma = shmat(shm_id1,NULL,0)) < 0)
    {
    	perror("shmat1");
    	return 0;
    }
    
  
    
    for( i = 0;i < n*n;i++)
    {
    	ma[i] = num;
    	num++;
    }

int sum = 0;
int sec,usec;
int shm_id3;

int m;

for(m = 1;m <= 16;m++)
{
	
	int np = m;
	int npid = 0;
	int* nexit;
	int shm_id_e;

	if((shm_id_e = shmget(0,1*sizeof(int),IPC_CREAT|0666)) < 0)
	{
			perror("shmgetEXIT");
			return 0;
	}
	if((nexit = shmat(shm_id_e,NULL,0)) < 0)
	{
			perror("shmatEXIT");
			return 0;
	}
	
	nexit[0] = 0;
	
    sum = 0;
    printf("Multiplying matrices using %d process\n",np);
    gettimeofday(&start,0);
    if((shm_id3 = shmget(0,n*n*sizeof(int),IPC_CREAT|0666)) < 0)
	{
			perror("shmget3");
			return 0;
	}
	
	pid_t pidd = fork();
	
	if(pidd==0)
	{
		exit(0);
	}
	
	

	for(i = 0;i < np;i++)
	{
		
		if(pidd<0)
		{
     	fprintf(stderr,"Fork Failed\n");
      	exit(-1);
   		}
   		else if(pidd>0)
   		{	
   		if((mc = shmat(shm_id3,NULL,0)) < 0)
			{
				perror("shmat3");
				return 0;
			}
   			pidd = fork();
   			npid++;
   		}
   		
   		
	}
	
if(pidd == 0)
{
	for(i = (npid-1)*n/np;i < n*(npid)/np;i++)
	{	
	//printf("i: %d\n",i); 
		for(j = 0;j < n;j++)
		{	
			mc[i*n+j] = 0;
			for(k = 0;k < n;k++)
			{
				mc[i*n+j] += (ma[i*n+k]*ma[k*n+j]);

				/*printf("number: %d %d\n",i*n+k,k*n+j);
				printf("ma:%d %d\n",ma[i*n+k],ma[k*n+j]);
				printf("product:%d\n",(i*n+k)*(k*n+j));
				printf("mc's:%d ",i*n+j);
				printf("mc[%d]:%d\n",i*n+j,mc[i*n+j]);*/
			}
		}		
	} 
}
	
//	printf("end\n");

	if(npid <= np && pidd == 0) 
	{
	//printf("exit %d\n",npid);
	nexit[0]++;
	Detach();
	exit(0);
	}
	else
	{
	wait(NULL);
	}
	//wait(NULL);
	while(nexit[0]!=np){};
	
	for(i = 0;i < n*n;i++)
	{
		//printf(" %d\n",mc[i]);
		sum+=mc[i];
	}
	
	Delete(shm_id3);
	
	gettimeofday(&end,0);
	sec = end.tv_sec - start.tv_sec;
    usec = end.tv_usec - start.tv_usec;
    printf("Elapsed time: %f sec", sec+(usec/1000000.0));
    printf(", Checksum: %d\n",sum);
	
	
}
	
    
    
    
    return 0;
}



void Detach()
{
	if (shmdt(mc) == -1) 
	{
    fprintf(stderr, "shmdt failed\n");
    exit(EXIT_FAILURE);
    }

}

void Delete(int shm_id)
{
	Detach();
	if (shmctl(shm_id, IPC_RMID, 0) == -1) 
	{
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        exit(1);
    }


}
/*
int ShmGet(
if((shm_id1 = shmget(key1,n*n*sizeof(int),IPC_CREAT|0666)) < 0)
    {
    	perror("shmget1");
    	return 0;
    }
    if((ma = shmat(shm_id1,NULL,0)) < 0)
    {
    	perror("shmat1");
    	return 0;
    }

*/

