#include <unistd.h>
#include <sys/param.h>
#include <stdio.h>

void	ft_print_cwd()
{
	char buff[MAXPATHLEN];

	printf("%s\n", getcwd(buff, MAXPATHLEN));

}

int main()
{
	ft_print_cwd();
	if (chdir("..")  == -1)
		perror("Error");
	ft_print_cwd();
	return (0);
}