/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection_out.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:43:45 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/30 03:20:28 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

static	int	ft_open_file(char *file_path, int redirection_type)
{
	int	fd;

	if (redirection_type == REDIRECTION)
		fd = open(ft_strtrim2(file_path, " "),
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redirection_type == APPEND_REDIRECTION)
		fd = open(ft_strtrim2(file_path, " "),
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = -1;
	return (fd);
}

static	void	ft_redicetion_error(char *msg, int *exit_status)
{
	perror(msg);
	*exit_status = 1;
}

void	ft_execute_redirection_out(t_tree *root, t_env **env, int *exit_status)
{
	int	fd;
	int	out;

	out = dup(1);
	if (out == -1)
		return (ft_redicetion_error("🍪: dup error", exit_status));
	fd = -1;
	if (root->left)
	{
		fd = ft_open_file(root->left->value, root->type);
		if (fd == -1)
		{
			close (out);
			return (ft_redicetion_error("🍪: open error", exit_status));
		}
	}
	dup2(fd, 1);
	close(fd);
	ft_execute(root->right, env, exit_status);
	dup2(out, 1);
	close(out);
}
