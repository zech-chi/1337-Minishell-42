/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:39:39 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/24 02:36:44 by zech-chi         ###   ########.fr       */
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

static void	ft_print_sorted_env(t_env **env)
{
	t_env	*left;
	t_env	*right;
	t_env	*cur;

	left = *env;
	while (left && left->next)
	{
		right = left->next;
		while (right)
		{
			if (ft_strcmp2(left->key, right->key) > 0)
			{
				ft_swap(left, right);
			}
			right = right->next;
		}
		left = left->next;
	}
	cur = *env;
	while (cur)
	{
		printf("declare -x %s=\"%s\"\n", cur->key, cur->value);
		cur = cur->next;
	}
	// must free env;
}

void	ft_export(t_env **env, char **cmd_2d)
{
	int		i;
	t_env	*env_dup;
	char	**one_by_one;

	if (!(cmd_2d[1]))
	{
		env_dup = ft_env_duplicate(*env);
		ft_print_sorted_env(&env_dup);
	}
	i = 0;
	while (cmd_2d[++i])
	{
		one_by_one = ft_split2(cmd_2d[i], '=');
		if (!one_by_one || !one_by_one[0] || !one_by_one[1])
			continue ;
		if (ft_env_update(env, one_by_one[0], one_by_one[1]))
			ft_env_add(env, one_by_one[0], one_by_one[1]);
	}
}
