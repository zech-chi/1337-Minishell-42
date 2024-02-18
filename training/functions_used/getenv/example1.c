#include <stdlib.h>
#include <stdio.h>

int main()
{
	printf("PATH=%s\n", getenv("PATH"));
	printf("HOME=%s\n", getenv("HOME"));
	printf("PWD=%s\n", getenv("PWD"));
	return (0);
}
