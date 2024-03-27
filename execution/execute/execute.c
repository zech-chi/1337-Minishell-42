/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:28:34 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/27 20:48:59 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

void	ft_execute_search_in_path(char **cmd_2d, t_env *env, char **env_2d)
{
	char	**path_2d;
	char	*path_1d;
	char	*cmd;
	int		r;

	path_1d = ft_env_search(env, "PATH");
	path_2d = ft_split2(path_1d, ':');
	if (!path_2d)
	{
		ft_put_error("🍪: malloc failed\n");
		free(path_1d);
		return ;
	}
	r = -1;
	while (path_2d[++r])
	{
		cmd = ft_strjoin2(ft_strdup2(path_2d[r]), ft_strjoin2(ft_strdup2("/"), ft_strdup2(cmd_2d[0])));
		execve(cmd, cmd_2d, env_2d);
		free(cmd);
	}
	free(path_1d);
	ft_free_2d_char(path_2d);
}

void	ft_execute_cmd(char *cmd, t_env **env, int *exit_status)
{
	char	**cmd_2d;
	char	**env_2d;
	pid_t	pid;

	cmd_2d = ft_expand(cmd, *env, *exit_status);
	if (!cmd_2d)
	{
		ft_put_error("🍪: malloc failed\n");
		return ;
	}
	if (ft_execute_builtins(cmd_2d, env, exit_status) == SUCCESS)
		return ;
	pid = fork();
	if (pid < 0)
	{
		ft_put_error("🍪: Fork Error\n");
		ft_free_2d_char(cmd_2d);
		return ;
	}
	else if (pid == 0)
	{
		env_2d = ft_env_create_2d(*env);
		if (!env_2d)
		{
			ft_put_error("🍪: malloc failed\n");
			return ;
		}
		execve(cmd_2d[0], cmd_2d, env_2d);
		ft_execute_search_in_path(cmd_2d, *env, env_2d);
		ft_put_error("🍪: Execution Error: ");
		ft_put_error(cmd_2d[0]);
		ft_put_error(" command not found\n");
		ft_free_2d_char(cmd_2d);
		ft_free_2d_char(env_2d);
		exit(127);
	}
	else
		waitpid(pid, exit_status, 0);
	*exit_status = WEXITSTATUS(*exit_status);
	ft_free_2d_char(cmd_2d);
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
