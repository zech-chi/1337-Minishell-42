/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:57:09 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/16 02:02:25 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

//int	ft_open_file(char *file_path, int redirection_type)
//{
//	int	fd;

//	if (redirection_type == REDIRECT_OUTPUT)
//		fd = open(ft_strtrim2(file_path, " "), O_WRONLY | O_CREAT | O_TRUNC, 0644);
//	else if (redirection_type == REDIRECT_OUTPUT_APPEND)
//		fd = open(ft_strtrim2(file_path, " "), O_WRONLY | O_CREAT | O_APPEND, 0644);
//	else
//		fd = -1;
//	return (fd);
//}

int	ft_execute_builtins(char **cmd_2d, t_env **env, int *exit_status)
{
	if (!cmd_2d || !(*cmd_2d))
		return (SUCCESS);
	else if (!ft_strcmp2("env", cmd_2d[0]))
		return (ft_env_print(*env), *exit_status = 0, SUCCESS);
	else if (!ft_strcmp2("exit", cmd_2d[0]))
		return (printf("exit\n") ,exit(SUCCESS), SUCCESS);
	//else if (!ft_strcmp2(PWD, cmd_2d[0]))
	//	return (ft_pwd_print(), SUCCESS);
	//else if (!ft_strcmp2(CD, cmd_2d[0]))
	//	return (ft_cd(cmd_2d, env));
	//else if (!ft_strcmp2(EXPORT, cmd_2d[0]))
	//	return (ft_export(env, cmd_2d));
	//else if (!ft_strcmp2(UNSET, cmd_2d[0]))
	//	return (ft_unset(env, cmd_2d));
	//else if (!ft_strcmp2("echo", cmd_2d[0]) && !ft_strcmp2("$?", cmd_2d[1]))
	//	return (printf("%d\n", status % 255), 0);
	else if (!ft_strcmp2("echo", cmd_2d[0]))
		return (ft_echo(cmd_2d), *exit_status = 0, SUCCESS);
	else
		return (FAILED);
}

void	ft_execute_search_in_path(char **cmd_2d, t_env *env)
{
	char	**path;
	char	*cmd;
	int		r;

	cmd = cmd_2d[0];
	path = ft_split2(ft_env_search(env, "PATH"), ':');
	if (!path)
		return ;
	r = -1;
	while (path[++r])
		execve(ft_strjoin2(path[r], ft_strjoin2("/", cmd)), cmd_2d, ft_env_create_2d(env));
}

void	ft_cmd_execute(char *cmd, t_env **env, int *exit_status)
{
	char	**cmd_2d;
	pid_t	pid;

	//cmd_2d = ft_split2(cmd, SPACE);
	cmd_2d = ft_expand(cmd, *env, *exit_status);
	if (!cmd_2d)
		exit(FAILED);
	if (ft_execute_builtins(cmd_2d, env, exit_status) == SUCCESS)
		return ;
	pid = fork();
	if (pid < 0)
	{
		perror("Fork Error");
		exit(FAILED);
	}
	else if (pid == 0)
	{
		execve(cmd_2d[0], cmd_2d, ft_env_create_2d(*env));
		ft_execute_search_in_path(cmd_2d, *env);
		perror("Execution Error");
		exit(FAILED);
	}
	else
	{
		waitpid(pid, exit_status, 0);
	}
}


void	ft_cmd_execute2(char *cmd, t_env **env, int *exit_status, int std)
{
	char	**cmd_2d;
	pid_t	pid;
	int		fd[2];

	//cmd_2d = ft_split2(cmd, SPACE);
	cmd_2d = ft_expand(cmd, *env, *exit_status);
	pipe(fd);
	if (!cmd_2d)
		exit(FAILED);
	if (ft_execute_builtins(cmd_2d, env, exit_status) == SUCCESS)
		return ;
	pid = fork();
	if (pid < 0)
	{
		perror("Fork Error");
		exit(FAILED);
	}
	else if (pid == 0)
	{
		close(fd[0]);
		if(std)
			dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execve(cmd_2d[0], cmd_2d, ft_env_create_2d(*env));
		ft_execute_search_in_path(cmd_2d, *env);
		perror("Execution Error");
		exit(FAILED);
	}
	//wait(exit_status);
	//printf("cmd: %s \n", cmd);
	//sleep(10);
	dup2 (fd[0], 0);
	close (fd[1]);
	close(fd[0]);
	//printf("wait\n");
	//sleep(10);
	(void)(exit_status);
}

void	ft_execute_pipe(t_tree *root, t_env **env, int *exit_status)
{
	int	pid1;
	int	pid2;
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("Error");
		return;
	}
	pid1 = 0;
	pid2 = 0;
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("Error");
		exit(FAILED);
	}
	else if (pid1 == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], 1) == -1)
		{
			perror("Error");
			exit(FAILED);
		}
		close(fd[1]);
		ft_execute(root->left, env, exit_status);
		exit(*exit_status);
	}
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("Error");
		exit(FAILED);
	}
	else if (pid2 == 0)
	{
		close(fd[1]);
		if (dup2(fd[0], 0) == -1)
		{
			perror("Error");
			exit(FAILED);
		}
		close(fd[0]);
		ft_execute(root->right, env, exit_status);
		exit(*exit_status);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, exit_status, 0);
	waitpid(pid2, exit_status, 0);
}

void	ft_execute(t_tree *root, t_env **env, int *exit_status)
{
	//int			fd;

	if (!root)
		return ;
	else if (root->type == PIPE)
		ft_execute_pipe(root, env, exit_status);
	//else if (root->type == REDIRECT_OUTPUT || root->type == REDIRECT_OUTPUT_APPEND)
	//{
	//	if (fork() == 0)
	//	{
	//		fd = ft_open_file(root->right->data, root->type);
	//		if (i == 0)
	//		{
	//			dup2(fd, STDOUT_FILENO);
	//			i++;
	//		}
	//		close(fd);
	//		if (root->left)
	//			ft_execute(root->left, env, exit_status, std_in);
	//		exit(*exit_status);
	//	}
	//	else 
	//		wait(exit_status);
	//}
	else if (root->type == AND)
	{
		ft_execute(root->left, env, exit_status);
		if ((*exit_status) == 0)
			ft_execute(root->right, env, exit_status);
	}
	else if (root->type == OR)
	{
		ft_execute(root->left, env, exit_status);
		if ((*exit_status) != 0)
			ft_execute(root->right, env, exit_status);
	}
	else
		ft_cmd_execute(root->value, env, exit_status);
}

