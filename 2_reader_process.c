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

        int * start_address = NULL;
        int * walk = NULL;
        int shmid = 0;
        int index = 0;
	int N = 1000;
	int average = 0;
	int max = 0;
	int min = 0;
	int sum = 0;

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
	min = start_address[0];
	max = start_address[0];
	
	
	for(index = 0; index < 100; ++index)
	{
		printf("%d\n",start_address[index]);
		sum += start_address[index];	
		if(start_address[index] < min)
		{
			min = start_address[index];
		}
		if(start_address[index] > max)
		{
			max = start_address[index];
		}
		
	}
	
	average = sum/100;
	printf("Average : %d\n", average);
	printf("Max : %d\n" , max);
	printf("Min : %d\n", min);
	
	
	
	return 0;
}

