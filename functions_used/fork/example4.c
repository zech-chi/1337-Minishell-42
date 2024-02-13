#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int	a;
	int	b;
	pid_t pid;

	a = 7;
	b = 11;
	pid = fork();
	if (pid == 0) {
		printf("the child calculate: a + b = %d\n", a + b);
	} else if (pid > 0) {
		printf("the parent calculate: a * b = %d\n", a * b);
	} else {
		perror("can't fork!");
	}
	return (0);
}