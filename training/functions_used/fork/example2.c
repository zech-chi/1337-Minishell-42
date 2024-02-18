#include <stdio.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;

	pid = fork();
	printf("hello world! pid = %d\n", pid);
}