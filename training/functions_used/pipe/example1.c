#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//void	ft_execute_cmd1(int fd[2])
//{
//	char	*cmd1 = {"/bin/ls", NULL};
//	int	pid;

//	pid = fork();
//	if (pid < 0) {
//		perror("fork");
//		exit(1);
//	} else if (pid == 0) {
//		execve(cmd1[0], cmd1, NULL);
//	} else {

//	}
//}
//void	ft_execute_cmd2(int fd[2])
//{
//	char	*cmd2 = {"/usr/bin/wc", "-l", NULL};
//}

int main()
{
	int	fd[2];
	int	pid;

	char	*cmd1[] = {"/bin/ls", NULL};
	char	*cmd2[] = {"/usr/bin/grep", "a", NULL};

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	pid = fork();
	if (pid < 0) {
		perror("fork");
		return (1);
	} else if (pid == 0) {
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		execve(cmd1[0], cmd1, NULL);
	} else {
		wait(NULL);
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		execve(cmd2[0], cmd2, NULL);
	}
	return (0);
}
