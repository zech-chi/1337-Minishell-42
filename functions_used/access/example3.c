#include <unistd.h>
#include <stdio.h>


int	main()
{
	char *pathname1 = "folder/test1.txt";
	char *pathname2 = "folder/test2.txt";

	if (access(pathname1, X_OK | R_OK | W_OK) == 0)
		printf("%s has all permissions\n", pathname1);
	else
		printf("%s does not has all permissions\n", pathname1);

	if (access(pathname2, X_OK | R_OK | W_OK) == 0)
		printf("%s has all permissions\n", pathname2);
	else
		printf("%s does not has all permissions\n", pathname2);
	return (0);
}