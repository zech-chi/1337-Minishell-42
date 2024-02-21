#include <dirent.h>
#include <stdio.h>


int	main()
{
	DIR	*dir = opendir("testfolder");
	struct dirent *entry;
	if (dir == NULL)
	{
		perror("Error");
		return (1);
	}
	printf("Directory opened successfully\n");
	while ((entry = readdir(dir)) != NULL)
	{
		//printf("entry->d_ino: %llu\n", entry->d_ino);
		printf("entry->d_name: %s\n", entry->d_name);
		printf("entry->d_namlen: %u\n", (unsigned int)entry->d_namlen);
		//printf("entry->d_reclen: %d\n", entry->d_reclen);
		//printf("entry->d_seekoff: %lld\n", entry->d_seekoff);
		printf("entry->d_type: %d\n", entry->d_type);
		printf("------------------------------------\n");
	}
}
