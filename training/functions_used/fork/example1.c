#include <stdio.h>
#include <unistd.h>

int main(void)
{
	if (fork() > 0)
		fork();
	printf("hello world!\n");
}