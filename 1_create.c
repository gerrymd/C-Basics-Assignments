#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#define KEY 0x020
#define SIZE 1000
#define PERM IPC_CREAT|S_IRUSR|S_IWUSR|S_IROTH|S_IWOTH
int main()
{
	if(shmget(KEY , SIZE , PERM) < 0)

	{
		perror("shmget");	
		exit(1);
	}
	else
	{
		printf("Shared memory segment created\n");
	}
	return 0;
}

