#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

#define KEY 0x010
#define SIZE 1000
#define PERM S_IRUSR|S_IWUSR|S_IROTH|S_IWOTH
int main()
{

        int * start_address;
        int * walk;
        int shmid;
        int index;
	int N = 1000;

        if((shmid = shmget(KEY , SIZE , PERM)) < 0)
        {
                perror("shmget");
                exit(1);
        }

        if((start_address = shmat(shmid , NULL , 0)) == (int*) - 1)
        {
                perror("shmat");
                exit(1);
	}
	
	for(index = 0 ; index < 100 ; index ++)
	{
		start_address[index] = rand() % N;
		printf("%d\n", start_address[index]);
	}
	
	
	
	return 0;
}

