#include <unistd.h>
#include <stdio.h>


int	main()
{
	char *pathname1 = "test1.txt";
	char *pathname2 = "test2.txt";
	
	if (access(pathname1, F_OK) == 0)
		printf("%s is exist\n", pathname1);
	else
		printf("%s doesn't exist\n", pathname1);
	
	if (access(pathname2, F_OK) == 0)
		printf("%s is exist\n", pathname2);
	else
		printf("%s doesn't exist\n", pathname2);
}