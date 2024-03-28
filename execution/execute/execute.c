/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:28:34 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/28 20:40:10 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

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
