#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	pid_t  pd = fork();

	if (pd == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			printf("%d  %d %d\n", getppid(), getpid(), i);
			sleep(1);
		}
		exit(0);
	}
	else
	{
		printf("hello world! pid = %d\n", getpid());
	}
	
}