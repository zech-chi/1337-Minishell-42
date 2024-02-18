#include <stdio.h>
#include <unistd.h>

int main()
{
	char *pathname = "folder/test1.txt";

	if (access(pathname, R_OK) == 0)
		printf("%s can read\n", pathname);
	else
		printf("%s can't read\n", pathname);

	if (access(pathname, W_OK) == 0)
		printf("%s can write \n", pathname);
	else
		printf("%s can't write\n", pathname);

	if (access(pathname, X_OK) == 0)
		printf("%s can execute\n", pathname);
	else
		printf("%s can't execute\n", pathname);
}