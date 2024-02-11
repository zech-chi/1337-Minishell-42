#include <unistd.h>
#include <stdio.h>


int	main()
{
	char *pathname = "folder/test2.txt";
	
	if (access(pathname, X_OK | R_OK | W_OK) == 0)
		printf("%s has all permissions\n", pathname);
	else
		printf("%s does not have all permissions\n", pathname);
	return (0);
}