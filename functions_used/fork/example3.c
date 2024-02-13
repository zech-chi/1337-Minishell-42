#include <stdio.h>
#include <unistd.h>

int main(void)
{
	fork();
	printf("hello world! pid = %d\n", getpid());
}