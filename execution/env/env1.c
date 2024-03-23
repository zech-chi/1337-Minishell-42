/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:50:15 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/16 17:17:11 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

// creat linked list env
// return env linked list on success, NULL otherwise
// I should clear env !!!!
// 		free(splited_row);
t_env	*ft_env_create(char **ev)
{
	t_env	*env;
	char	**splited_row;
	int		r;
	int		c;
	char	*value;

	r = -1;
	env = NULL;
	while (ev[++r])
	{
		splited_row = ft_split2(ev[r], EQUAL);
		if (!splited_row)
			return (NULL);
		c = 0;
		value = NULL;
		while (splited_row[++c])
		{
			if (c == 1)
				value = ft_strjoin2(value, splited_row[c]);
			else
				value = ft_strjoin2(value, ft_strjoin2("=", splited_row[c]));
		}
		ft_env_add(&env, splited_row[0], value);
	}
	return (env);
}

char	**ft_env_create_2d(t_env *env)
{
	char	**env_2d;
	int		r;

	env_2d = malloc(sizeof(char *) * (ft_env_size(env) + 1));
	if (!env_2d)
		return (NULL);
	r = 0;
	while (env)
	{
		env_2d[r++] = ft_strjoin2(ft_strdup2(env->key),
				ft_strjoin2("=", ft_strdup2(env->value)));
		env = env->next;
	}
	env_2d[r] = NULL;
	return (env_2d);
}

int	ft_env_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

// free env linked list with all its staffs
void	ft_env_clear(t_env **env)
{
	t_env	*cur_node;
	t_env	*nxt_node;

	if (!env)
		return ;
	cur_node = *env;
	while (cur_node)
	{
		nxt_node = cur_node->next;
		free(cur_node->key);
		free(cur_node->value);
		free(cur_node);
		cur_node = nxt_node;
	}
	*env = NULL;
}
