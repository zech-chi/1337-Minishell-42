/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection_out.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:43:45 by zech-chi          #+#    #+#             */
/*   Updated: 2024/04/17 11:42:44 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

static int	ft_open_file(char *file_path, int redirection_type, int *ex)
{
	int	fd;

	if (redirection_type == REDIRECTION)
		fd = open(file_path,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redirection_type == APPEND_REDIRECTION)
		fd = open(file_path,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = -1;
	if (fd != -1)
		*ex = 0;
	return (fd);
}

static void	ft_redicetion_out_error(char *msg, int *exit_status)
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

void	ft_execute_redirection_out(t_tree *root, t_env **env, int *exit_status)
{
	int		fd;
	int		out;
	char	**file_path;

	out = dup(1);
	if (out == -1)
		return (ft_redicetion_out_error("🍪: dup error", exit_status));
	if (!(root->left))
		return ;
	file_path = ft_expand(root->left->value, *env, *exit_status);
	if (!file_path || !(*file_path))
		return (ft_error2(exit_status, file_path, root->left->value));
	fd = ft_open_file(*file_path, root->type, exit_status);
	if (fd == -1)
	{
		close(out);
		ft_free_2d_char(file_path);
		return (ft_redicetion_out_error("🍪: open error", exit_status));
	}
	dup2(fd, 1);
	close(fd);
	ft_execute(root->right, env, exit_status);
	dup2(out, 1);
	close(out);
	ft_free_2d_char(file_path);
}
