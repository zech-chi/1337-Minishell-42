/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 21:08:08 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/06 11:34:11 by zech-chi         ###   ########.fr       */
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

//void	ft_cmd_execute(char *cmd, t_env **env)
//{
//	char	**cmd_2d;
//	//pid_t	pid;

//	cmd_2d = ft_split(cmd, SPACE);
//	if (!cmd_2d)
//		exit(FAILED);

//	execve(cmd_2d[0], cmd_2d, ft_env_create_2d(*env));
//	ft_execute_search_in_path(cmd_2d, *env);
//	perror("Execution Error");
//}
void	ft_cmd_execute(char *cmd, t_env **env, int *exit_status, int std)
{
	char	**cmd_2d;
	pid_t	pid;
	int		fd[2];

	cmd_2d = ft_split(cmd, SPACE);
	pipe(fd);
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
		close(fd[0]);
		if(std)
			dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execve(cmd_2d[0], cmd_2d, ft_env_create_2d(*env));
		ft_execute_search_in_path(cmd_2d, *env);
		perror("Execution Error");
		exit(FAILED);
	}
	dup2 (fd[0], 0);
	close (fd[1]);
	close(fd[0]);
	wait(exit_status);
}

void	ft_execute_pipe(t_node *root, t_env **env, int *exit_status)
{

	if (root && root->type == PIPE)
	{
		ft_cmd_execute(root->left->data, env, exit_status, 1);
		//save = root->left;
		if (root->right->type == PIPE)
			ft_execute_pipe(root->right, env, exit_status);
		else
		{
			ft_cmd_execute(root->right->data, env, exit_status, 0);
		}
	}
	else
	{
		ft_cmd_execute(root->data, env, exit_status , 0);
	}
}


void	ft_execute(t_node *root, t_env **env, int *exit_status)
{
	//pid_t	pid;
	//static int	i;
	////static int	j;
	//int			fd;

	if (!root)
		return ;
	else if (root->type == PIPE)
	{
		ft_execute_pipe(root, env, exit_status);
	}
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
	//			ft_execute(root->left, env, exit_status);
	//		exit(*exit_status);
	//	}
	//	else 
	//		wait(exit_status);
	//}
	//else if (root->type == AND)
	//{
	//	ft_execute(root->left, env, exit_status);
	//	if ((*exit_status) == 0)
	//		ft_execute(root->right, env, exit_status);
	//}
	//else if (root->type == OR)
	//{
	//	ft_execute(root->left, env, exit_status);
	//	if ((*exit_status) != 0)
	//		ft_execute(root->right, env, exit_status);
	//}
	else
		ft_cmd_execute(root->data, env, exit_status, 0);
}


char	*ft_get_prompt()
{
	char	*prompt;

	prompt = readline("🍪🍪🍪\033[0;32m>$ \033[0m");
	if (prompt && prompt[0])
		add_history(prompt);
	return (prompt);
}

int	main(int ac, char **av, char **ev)
{
	t_env	*env;
	t_node	*root;
	int	exit_status;
	//int out =

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
//		ft_expand(prompt);
//		//ft_reset();
//		//ft_execute(prompt, &env);
//	}
//	return (0);
//}