/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:39:39 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/31 02:22:23 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

static void	ft_swap(t_env	*node1, t_env	*node2)
{
	char	*tmp_value;
	char	*tmp_key;

	tmp_key = node1->key;
	tmp_value = node1->value;
	node1->key = node2->key;
	node2->key = tmp_key;
	node1->value = node2->value;
	node2->value = tmp_value;
}

static void	ft_print_sorted_env(t_env **env_dup)
{
	t_env	*left;
	t_env	*right;
	t_env	*cur;

	left = *env_dup;
	while (left && left->next)
	{
		right = left->next;
		while (right)
		{
			if (ft_strcmp2(left->key, right->key) > 0)
				ft_swap(left, right);
			right = right->next;
		}
		left = left->next;
	}
	cur = *env_dup;
	while (cur)
	{
		printf("declare -x %s", cur->key);
		// modified
		if (cur->value && (cur->visible))
		{
			printf("=\"%s\"", cur->value);
		}
		//////
		printf("\n");
		cur = cur->next;
	}
}

void	ft_export(t_env **env, char **cmd_2d, int *exit_status)
{
	int		i;
	t_env	*env_dup;

	*exit_status = 0;
	if (!(cmd_2d[1]))
	{
		env_dup = ft_env_duplicate(*env);
		ft_print_sorted_env(&env_dup);
		ft_env_clear(&env_dup);
	}
	i = 0;
	while (cmd_2d[++i])
		ft_export_help(cmd_2d[i], env, exit_status);
}
