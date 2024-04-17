/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection_in.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 03:35:59 by zech-chi          #+#    #+#             */
/*   Updated: 2024/04/17 11:48:36 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

static int	ft_open_file(char *file_path, int *exit_status)
{
	int	fd;

	fd = -1;
	fd = open(file_path, O_RDONLY);
	if (fd != -1)
		*exit_status = 0;
	return (fd);
}

static void	ft_error1(char *msg, int *exit_status)
{
	perror(msg);
	*exit_status = 1;
}

static void	ft_error2(int *exit_status, char **file_path, char *msg)
{
	ft_put_error("🍪: ");
	ft_put_error(msg);
	ft_put_error(": ambiguous redirect\n");
	*exit_status = 1;
	ft_free_2d_char(file_path);
}

void	ft_execute_redirection_in(t_tree *root, t_env **env, int *exit_status)
{
	int		fd;
	int		in;
	char	**file_path;

	in = dup(0);
	if (in == -1)
		return (ft_error1("🍪: dup error", exit_status));
	if (!root->left)
		return ;
	file_path = ft_expand(root->left->value, *env, *exit_status);
	if (!file_path || !(*file_path))
		return (ft_error2(exit_status, file_path, root->left->value));
	fd = ft_open_file(*file_path, exit_status);
	if (fd == -1)
	{
		close(in);
		ft_free_2d_char(file_path);
		return (ft_error1("🍪: open error", exit_status));
	}
	dup2(fd, 0);
	close(fd);
	ft_execute(root->right, env, exit_status);
	dup2(in, 0);
	close(in);
	ft_free_2d_char(file_path);
}
