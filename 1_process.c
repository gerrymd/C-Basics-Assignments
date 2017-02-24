#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

#define KEY 0x020
#define SIZE 1000
#define PERM S_IRUSR|S_IWUSR|S_IROTH|S_IWOTH
int main()
{	
	
	char * start_address;
	char * walk;
	int shmid;
	char buffer[] = "This is a string";
	struct shmid_ds stat_buff;
	pid_t pid;
	int index;
	
	if((shmid = shmget(KEY , SIZE , PERM)) < 0)
	{
		perror("shmget");
		exit(1);
	}
	
	if((start_address = shmat(shmid , NULL , 0)) == (char*) - 1)
	{
		perror("shmat");
		exit(1);
	}
	
	if(shmctl(shmid , IPC_STAT, &stat_buff) < 0)
	{
		perror("shmctl");
		exit(1);
	}
	printf("Number of processes attached : %d\n" , stat_buff.shm_nattch);
	
	for(index = 0; index < strlen(buffer) ; ++index)
	{
		start_address[index] = buffer[index];
	}
	
	
	if((pid = fork()) < 0 )
	{
		perror("fork");
		exit(1);
	}
		
	else if(pid)
	{
		if(shmctl(shmid , IPC_STAT , &stat_buff) < 0)
		{
			perror("shmctl");
			exit(1);	
		}
		printf("Number of attached processes : %d\n", stat_buff.shm_nattch);
		printf("String in parent before : %s\n", start_address);
		if(waitpid(pid , NULL , 0) < 0)
		{
			perror("waitpid");
			exit(1);
		}
		printf("String in parent after : %s\n", start_address);
	}
	else//child
	{	
		for(index = 0; index < strlen(buffer) ; ++index)
		{
			start_address[index] = toupper(start_address[index]);
		}
		printf("String in child : %s\n", start_address);
	}

	
	
	
	
	return 0;
}
