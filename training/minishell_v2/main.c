/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 21:08:08 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/02 21:12:20 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header/minishell_v2.h"

int	ft_open_file(char *file_path, int redirection_type)
{
	int	fd;

	if (redirection_type == REDIRECT_OUTPUT)
		fd = open(ft_strtrim(file_path, " "), O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redirection_type == REDIRECT_OUTPUT_APPEND)
		fd = open(ft_strtrim(file_path, " "), O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = -1;
	return (fd);
}

void	ft_execute_search_in_path(char **cmd_2d, t_env *env)
{
	char	**path;
	char	*cmd;
	int		r;

	cmd = cmd_2d[0];
	path = ft_split(ft_env_search(env, "PATH"), ':');
	if (!path)
		return ;
	r = -1;
	while (path[++r])
		execve(ft_strjoin(path[r], ft_strjoin("/", cmd)), cmd_2d, ft_env_create_2d(env));
}

//void	ft_execute_redirection_output(t_node *root, t_env **env, int outfd)
//{
//	int	fd;
//	if (!root)
//		return ;
	
//	if (root->type == REDIRECT_OUTPUT || root->type == REDIRECT_OUTPUT_APPEND)
//	{
//		fd = ft_open_file(root->right->data, root->type);
//		if (fd == -1)
//		{
//			perror("open Error");
//			exit(FAILED);
//		}
//		close(fd);
//		ft_execute_redirection_output(root->left, env, outfd);
//	}
//	else
//	{
//		ft_cmd_execute(root->data, env);
//		close(outfd);
//	}
//}


//void	ft_execute_pipe(t_node *root, t_env **env, t_node *save)
//{
//	if (root && root->type == PIPE)
//	{
//		ft_cmd_execute1(root->left->data, env, &root->left, save);
//		save = root->left;
//		if (root->right->type == PIPE)
//			ft_execute_pipe(root->right, env, save);
//		else
//		{
//			ft_cmd_execute2(root->right->data, env, save);
//		}
//	}
//	else
//	{
//		ft_cmd_execute2(root->data, env, save);
//	}
//}

void	ft_cmd_execute(char *cmd, t_env **env, int *exit_status)
{
	char	**cmd_2d;
	pid_t	pid;

	cmd_2d = ft_split(cmd, SPACE);
	if (!cmd_2d)
		exit(FAILED);
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
		wait(exit_status);
	}
}

void	ft_execute(t_node *root, t_env **env, int *exit_status)
{
	//pid_t	pid;
	if (!root)
		return ;
	//if (root->type == REDIRECT_OUTPUT || root->type == REDIRECT_OUTPUT_APPEND)
	//	ft_execute_redirection_output(root, env, ft_open_file(root->right->data, root->type));
	if (root->type == AND)
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
		ft_cmd_execute(root->data, env, exit_status);
	//if (root->type == PIPE)
	//{
	//	t_node *save;
	//	ft_cmd_execute(root->left->data, env, &root->left);
	//	save = root->left;
	//	ft_execute_pipe(root->right, env, save);
	//}
	
}


int	main(int ac, char **av, char **ev)
{
	t_env	*env;
	t_node	*root;
	int	exit_status;

	(void)(ac);
	(void)(av);
	(void)(ev);
	root = ft_build_tree();
	ft_inorder_traversal(root);
	printf("-------------- don't look up -----------------\n");
	printf("----------------------------------------------\n");
	env = ft_env_create(ev);
	//ft_env_print(env);
	exit_status = 0;
	ft_execute(root, &env, &exit_status);
	printf("return back\n");
	//while (1);
	return (0);
}

// this function ask user to enter prompt
// and if prompt not NULL it add it to history

//char	*ft_get_prompt()
//{
//	char	*prompt;

//	prompt = readline("🍪🍪🍪\033[0;32m>$ \033[0m");
//	if (prompt && prompt[0])
//		add_history(prompt);
//	return (prompt);
//}




//int	main(int ac, char **av, char **ev)
//{
//	char	*prompt;
//	//t_env	*env;

//	(void)(ac);
//	(void)(av);
//	(void)(ev);
//	//env = ft_env_create(ev);
//	while (1)
//	{
//		prompt = ft_get_prompt();
//		if (prompt == NULL)
//		{
//			printf("exit\n");
//			exit(0);
//		}
//		//ft_parse(prompt);
//		//ft_execute(prompt, &env);
//	}
//	return (0);
//}

//void	ft_execute(t_node *root, t_env **env, int fd[2])
//{
//	int	pid;

//	if (!root)
//		return ;
//	if (root->type == PIPE)
//	{
//		if (pipe(fd) == -1)
//		{
//			perror("Pipe Error");
//			return ;
//		}
//		pid = fork();
//		if (pid < 0) {
//			perror("fork Error");
//			return ;
//		} else if (pid == 0) {
//			close(fd[0]);
//			dup2(fd[1], 1);
//			close(fd[1]);
//			ft_cmd_execute(root->left->data, env);
//			exit(FAILED);
//		} else {
//			wait(NULL);
//			close(fd[1]);
//			dup2(fd[0], 0);
//			close(fd[0]);
//			ft_cmd_execute(root->right->data, env);
//			exit(FAILED);
//		}
//	}
//}


//void	ft_cmd_execute(char *cmd, t_env **env)
//{
//	char	**cmd_2d;
//	pid_t	pid;

//	cmd_2d = ft_split(cmd, SPACE);
//	if (!cmd_2d)
//		exit(FAILED);
//	pid = fork();
//	if (pid < 0)
//	{
//		perror("Fork Error");
//		exit(FAILED);
//	}
//	else if (pid == 0)
//	{
//		execve(cmd_2d[0], cmd_2d, ft_env_create_2d(*env));
//		ft_execute_search_in_path(cmd_2d, *env);
//		perror("Execution Error");
//		exit(FAILED);
//	}
//	else
//	{
//		wait(NULL);
//		exit(SUCCESS);
//	}
//}


//void	ft_cmd_execute(char *cmd, t_env **env, t_node **root)
//{
//	char	**cmd_2d;
//	pid_t	pid;

//	pipe((*root)->fd);
//	cmd_2d = ft_split(cmd, SPACE);
//	if (!cmd_2d)
//		exit(FAILED);
//	pid = fork();
//	if (pid < 0)
//	{
//		perror("Fork Error");
//		exit(FAILED);
//	}
//	else if (pid == 0)
//	{
//		close((*root)->fd[0]);
//		dup2((*root)->fd[1], STDOUT_FILENO);
//		close((*root)->fd[1]);
//		execve(cmd_2d[0], cmd_2d, ft_env_create_2d(*env));
//		ft_execute_search_in_path(cmd_2d, *env);
//		perror("Execution Error");
//		exit(FAILED);
//	}
//	wait(NULL);
//}

//void	ft_cmd_execute1(char *cmd, t_env **env, t_node **root, t_node *save)
//{
//	char	**cmd_2d;
//	pid_t	pid;

//	pipe((*root)->fd);
//	cmd_2d = ft_split(cmd, SPACE);
//	if (!cmd_2d)
//		exit(FAILED);
//	pid = fork();
//	if (pid < 0)
//	{
//		perror("Fork Error");
//		exit(FAILED);
//	}
//	else if (pid == 0)
//	{
//		close(save->fd[1]);
//		dup2(save->fd[0], STDIN_FILENO);
//		close(save->fd[0]);
//		close((*root)->fd[0]);
//		dup2((*root)->fd[1], STDOUT_FILENO);
//		close((*root)->fd[1]);
//		execve(cmd_2d[0], cmd_2d, ft_env_create_2d(*env));
//		ft_execute_search_in_path(cmd_2d, *env);
//		perror("Execution Error");
//		exit(FAILED);
//	}
//	close(save->fd[0]);
//	close(save->fd[1]);
//	wait(NULL);
//}

//void	ft_cmd_execute2(char *cmd, t_env **env, t_node *save)
//{
//	char	**cmd_2d;
//	pid_t	pid;

//	cmd_2d = ft_split(cmd, SPACE);
//	if (!cmd_2d)
//		exit(FAILED);
//	pid = fork();
//	if (pid < 0)
//	{
//		perror("Fork Error");
//		exit(FAILED);
//	}
//	else if (pid == 0)
//	{
//		close(save->fd[1]);
//		dup2(save->fd[0], STDIN_FILENO);
//		close(save->fd[0]);
//		execve(cmd_2d[0], cmd_2d, ft_env_create_2d(*env));
//		ft_execute_search_in_path(cmd_2d, *env);
//		perror("Execution Error");
//		exit(FAILED);
//	}
//	close(save->fd[0]);
//	close(save->fd[1]);
//	wait(NULL);
//}