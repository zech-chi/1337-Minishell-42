#include <stdio.h>
#include <dirent.h>

int	main()
{
	DIR *dir = opendir("testfolder");
	if (dir != NULL) {
		printf("Directory opened successfully.\n");
		if (closedir(dir) == 0) {
			printf("Directory closed successfully.\n");
		} else {
			perror("Error");
			return (1);
		}
	} else {
		perror("Error");
		return (1);
	}

	return (0);
}
