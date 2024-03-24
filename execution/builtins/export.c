/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:39:39 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/24 04:15:44 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

static int	ft_is_valid_identifier(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if ('0' <= str[i] && str[i] <= '9' && i == 0)
			return (0);
		if (
			!(
			('0' <= str[i] && str[i] <= '9')
			|| ('a' <= str[i] && str[i] <= 'z')
			|| ('A' <= str[i] && str[i] <= 'Z')
			|| str[i] == '_'
			)
		)
			return (0);
		i++;
	}
	return (1);
}

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

char	*ft_get_part(char *str, int	*right)
{
	char	*first_part;
	int		left;

	if (!str)
		return (NULL);
	left = *right - 1;
	while (str[*right] != '=')
		(*right)++;
	first_part = (char *)malloc(sizeof(char) * (*right + 1));
	while (++left < *right)
		first_part[left] = str[left];
	first_part[left] = '\0';
	return (first_part);
}


void	ft_export(t_env **env, char **cmd_2d)
{
	int		i;
	t_env	*env_dup;
	char	*part1;
	char	*part2;
	int		right;

	if (!(cmd_2d[1]))
	{
		env_dup = ft_env_duplicate(*env);
		ft_print_sorted_env(&env_dup);
	}
	i = 0;
	while (cmd_2d[++i])
	{
		right = 0;
		part1;
		//one_by_one = ft_split2(cmd_2d[i], '=');
		//if (!one_by_one || !one_by_one[0] || !one_by_one[1])
		//	continue ;
		//if (ft_env_update(env, one_by_one[0], one_by_one[1]))
		//	ft_env_add(env, one_by_one[0], one_by_one[1], 1);
	}
	ft_is_valid_identifier(NULL);
}
//aa=