#include <stdio.h>
#include <dirent.h>

int	main()
{
	DIR *dir = opendir("folder2");
	if (dir != NULL) {
		printf("Directory opened successfully.\n");
		closedir(dir);
	} else {
		perror("Error");
	}
	return (0);
}