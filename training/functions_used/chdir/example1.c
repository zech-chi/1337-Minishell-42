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
	if (chdir("/Users/zech-chi/Desktop/1337-Minishell-42")  == -1)
		perror("Error");
	ft_print_cwd();
	return (0);
}