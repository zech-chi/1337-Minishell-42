/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:55:59 by zech-chi          #+#    #+#             */
/*   Updated: 2024/04/16 12:10:40 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

static void	ft_l_child(t_tree *root, t_env **env, int *exit_status, int fd[2])
{
	close(fd[0]);
	if (dup2(fd[1], 1) == -1)
	{
		ft_put_error("🍪: dup2 Error\n");
		exit(FAILED);
	}
	close(fd[1]);
	ft_execute(root->left, env, exit_status);
	exit(*exit_status);
}

static void	ft_r_child(t_tree *root, t_env **env, int *exit_status, int fd[2])
{
	close(fd[1]);
	if (dup2(fd[0], 0) == -1)
	{
		ft_put_error("🍪: dup2 Error\n");
		exit(FAILED);
	}
	close(fd[0]);
	ft_execute(root->right, env, exit_status);
	exit(*exit_status);
}

//*exit_status = WEXITSTATUS(*exit_status);
void	ft_execute_pipe(t_tree *root, t_env **env, int *exit_status)
{
	int	pid1;
	int	pid2;
	int	fd[2];

	if (pipe(fd) == -1)
		return (ft_put_error("🍪: pipe Error\n"));
	pid1 = 0;
	pid2 = 0;
	pid1 = fork();
	if (pid1 < 0)
		return (ft_put_error("🍪: fork Error\n"));
	else if (pid1 == 0)
		ft_l_child(root, env, exit_status, fd);
	pid2 = fork();
	if (pid2 == -1)
		return (ft_put_error("🍪: fork Error\n"), exit(FAILED));
	else if (pid2 == 0)
		ft_r_child(root, env, exit_status, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, exit_status, 0);
	waitpid(pid2, exit_status, 0);
	*exit_status = update_status(*exit_status);
}
