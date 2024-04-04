/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 20:39:26 by zech-chi          #+#    #+#             */
/*   Updated: 2024/04/03 04:03:23 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

static void	ft_execute_search_in_path(char **cmd_2d, t_env *env, char **env_2d)
{
	char	**path_2d;
	char	*path_1d;
	char	*cmd;
	int		r;

	path_1d = ft_env_search(env, "PATH");
	path_2d = ft_split2(path_1d, ':');
	if (!path_2d)
	{
		free(path_1d);
		return ;
	}
	r = -1;
	while (path_2d[++r])
	{
		cmd = ft_strjoin2(ft_strdup2(path_2d[r]),
				ft_strjoin2(ft_strdup2("/"), ft_strdup2(cmd_2d[0])));
		execve(cmd, cmd_2d, env_2d);
		free(cmd);
	}
	free(path_1d);
	ft_free_2d_char(path_2d);
}

static void	ft_child_job(t_env **env, char	**cmd_2d)
{
	char	**env_2d;

	env_2d = ft_env_create_2d(*env);
	if (!env_2d)
		return (ft_put_error("🍪: malloc failed\n"), exit(1));
	execve(cmd_2d[0], cmd_2d, env_2d);
	ft_execute_search_in_path(cmd_2d, *env, env_2d);
	ft_put_error("🍪: Execution Error: ");
	ft_put_error(cmd_2d[0]);
	ft_put_error(" command not found\n");
	ft_free_2d_char(cmd_2d);
	ft_free_2d_char(env_2d);
	exit(127);
}


/////

int	update_status(int status)
{
	if (WIFSIGNALED(status))   // check if process recived a signal
	{
		if (WTERMSIG(status) == SIGINT)
		{
			printf("\n");
			return (130);
		}
		if (WTERMSIG(status) == SIGQUIT)
		{
			printf("Quit: 3\n");
			return (131);
		}
	}
	if (WIFEXITED(status)) // to check if the process terminted with exit 
		return (WEXITSTATUS(status));
	return (1);
}

///

void	ft_execute_cmd(char *cmd, t_env **env, int *exit_status)
{
	char	**cmd_2d;
	pid_t	pid;

	cmd_2d = ft_expand(cmd, *env, *exit_status);
	if (!cmd_2d)
		return (ft_put_error("🍪: malloc failed\n"));
	if (ft_execute_builtins(cmd_2d, env, exit_status) == SUCCESS)
		return (ft_free_2d_char(cmd_2d));
	pid = fork();
	if (pid < 0)
	{
		ft_put_error("🍪: Fork Error\n");
		ft_free_2d_char(cmd_2d);
		return ;
	}
	else if (pid == 0)
		ft_child_job(env, cmd_2d);
	else
		waitpid(pid, exit_status, 0);
	//*exit_status = WEXITSTATUS(*exit_status);
	*exit_status = update_status(*exit_status);
	ft_free_2d_char(cmd_2d);
}
