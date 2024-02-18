#include <unistd.h>
#include <sys/param.h>
#include <stdio.h>

int main()
{
	char buff[MAXPATHLEN];

	printf("%s\n", getcwd(buff, MAXPATHLEN));
	return (0);
}