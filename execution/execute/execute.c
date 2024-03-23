/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:28:34 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/23 21:10:32 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

//int	ft_open_file(char *file_path, int redirection_type)
//{
//	int	fd;

//	if (redirection_type == REDIRECT_OUTPUT)
//		fd = open(ft_strtrim2(file_path, " "),
//			O_WRONLY | O_CREAT | O_TRUNC, 0644);
//	else if (redirection_type == REDIRECT_OUTPUT_APPEND)
//		fd = open(ft_strtrim2(file_path, " "),
//			O_WRONLY | O_CREAT | O_APPEND, 0644);
//	else
//		fd = -1;
//	return (fd);
//}

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
	{
		execve(ft_strjoin2(path[r], ft_strjoin2("/", cmd)),
			cmd_2d, ft_env_create_2d(env));
	}
}

void	ft_execute_cmd(char *cmd, t_env **env, int *exit_status)
{
	char	**cmd_2d;
	pid_t	pid;

	cmd_2d = ft_expand(cmd, *env, *exit_status);
	if (!cmd_2d)
		exit(FAILED);
	if (ft_execute_builtins(cmd_2d, env, exit_status) == SUCCESS)
		return ;
	pid = fork();
	if (pid < 0)
	{
		ft_put_error("🍪: Fork Error\n");
		exit(FAILED);
	}
	else if (pid == 0)
	{
		execve(cmd_2d[0], cmd_2d, ft_env_create_2d(*env));
		ft_execute_search_in_path(cmd_2d, *env);
		ft_put_error("🍪: Execution Error: ");
		ft_put_error(cmd_2d[0]);
		ft_put_error(" command not found\n");
		exit(FAILED);
	}
	else
		waitpid(pid, exit_status, 0);
}

static void	ft_execute_and(t_tree *root, t_env **env, int *exit_status)
{
	ft_execute(root->left, env, exit_status);
	if ((*exit_status) == 0)
		ft_execute(root->right, env, exit_status);
}

static void	ft_execute_or(t_tree *root, t_env **env, int *exit_status)
{
	ft_execute(root->left, env, exit_status);
	if ((*exit_status) != 0)
		ft_execute(root->right, env, exit_status);
}

void	ft_execute(t_tree *root, t_env **env, int *exit_status)
{
	if (!root)
		return ;
	else if (root->type == PIPE)
		ft_execute_pipe(root, env, exit_status);
	else if (root->type == REDIRECTION || root->type == APPEND_REDIRECTION)
		ft_execute_redirection_out(root, env, exit_status);
	else if (root->type == AND)
		ft_execute_and(root, env, exit_status);
	else if (root->type == OR)
		ft_execute_or(root, env, exit_status);
	else
		ft_execute_cmd(root->value, env, exit_status);
}
