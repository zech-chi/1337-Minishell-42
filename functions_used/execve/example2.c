#include <unistd.h>
#include <stdio.h>

int main(void)
{
	char *argv[] = {"/bin/ls", "-l", "-a", NULL};
	char *env[] = {"PATH=/bin/ls", NULL};

	if (fork() == 0)
	{
		if (execve(argv[0], argv, env) == -1)
			perror("Error");
	}
	printf("done\n");
	return (0);
}