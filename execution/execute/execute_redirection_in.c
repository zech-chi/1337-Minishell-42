/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection_in.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 03:35:59 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/30 03:52:20 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

static	void	ft_redicetion_in_error(char *msg, int *exit_status)
{
	perror(msg);
	*exit_status = 1;
}

void	ft_execute_redirection_in(t_tree *root, t_env **env, int *exit_status)
{
	int	fd;
	int	in;

	in = dup(0);
	if (in == -1)
		return (ft_redicetion_in_error("🍪: dup error", exit_status));
	if (!root->left)
		return ;
	fd = open(ft_strtrim2(root->left->value, " \t\v\n\f\r"), O_RDONLY);
	if (fd == -1)
	{
		close(in);
		return (ft_redicetion_in_error("🍪: open error", exit_status));
	}
	dup2(fd, 0);
	close(fd);
	ft_execute(root->right, env, exit_status);
	dup2(in, 0);
	close(in);
}
