#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	pid_t pid = fork();
	int n;

	if (pid == 0)
		n = 1;
	else if (pid > 0)
		n = 6;
	else
	{
		perror("can't fork");
		exit(1);
	}

	if (pid != 0)
		wait(NULL);
	
	for (int i = n; i < n + 5; i++)
	{
		printf("%d\n", i);
		usleep(100000);
	}

	if (pid != 0)
		printf("done!\n");
	
	return (0);
}
