#include <stdio.h>
#include <unistd.h>

int main(void)
{
	fork();
	fork();
	fork();
	printf("hello world!\n");
}
// 2 ^ n = 2 ^ 3 = 8