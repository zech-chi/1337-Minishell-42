/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:39:39 by zech-chi          #+#    #+#             */
/*   Updated: 2024/04/04 21:17:49 by zech-chi         ###   ########.fr       */
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

static void	ft_print_sorted_env(t_env *env_dup)
{
	t_env	*cur;

	cur = env_dup;
	while (cur)
	{
		if (ft_strcmp2(cur->key, "_"))
		{
			printf("declare -x %s", cur->key);
			if (cur->value && (cur->visible))
				printf("=\"%s\"", cur->value);
			printf("\n");
		}
		cur = cur->next;
	}
}

static void	ft_env_sort(t_env **env_dup)
{
	t_env	*left;
	t_env	*right;

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
}

void	ft_export_error(char *slice1, char *slice2, int equal, int append)
{
	ft_put_error("🍪: export: `");
	ft_put_error(slice1);
	if (equal)
		ft_put_error("=");
	else if (append == 1)
		ft_put_error("+");
	ft_put_error(slice2);
	ft_put_error("': not a valid identifier\n");
	free(slice1);
	free(slice2);
}

void	ft_export(t_env **env, char **cmd_2d, int *exit_status)
{
	int		i;
	t_env	*env_dup;

	*exit_status = 0;
	if (!(cmd_2d[1]))
	{
		env_dup = ft_env_duplicate(*env);
		ft_env_sort(&env_dup);
		ft_print_sorted_env(env_dup);
		ft_env_clear(&env_dup);
	}
	i = 0;
	while (cmd_2d[++i])
		ft_export_help(cmd_2d[i], env, exit_status);
}
