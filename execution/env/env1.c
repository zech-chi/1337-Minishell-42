/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:50:15 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/27 21:40:45 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

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
				value = ft_strjoin2(value, ft_strdup2(splited_row[c]));
			else
				value = ft_strjoin2(value, ft_strjoin2(ft_strdup2("="), ft_strdup2(splited_row[c])));
		}
		ft_env_add_at_create(&env, ft_strdup2(splited_row[0]), ft_strdup2(value), 1);
		free(value);
		ft_free_2d_char(splited_row);
	}
	ft_env_delete(&env, "OLDPWD");
	ft_env_add(&env, ft_strdup2("OLDPWD"), ft_strdup2(""), 0);
	return (env);
}

t_env	*ft_env_duplicate(t_env *env)
{
	t_env	*env_dup;

	env_dup = NULL;
	while (env)
	{
		ft_env_add(&env_dup, ft_strdup2(env->key), ft_strdup2(env->value), env->visible);
		env = env->next;
	}
	return (env_dup);
}

char	**ft_env_create_2d(t_env *env)
{
	char	**env_2d;
	int		r;

	env_2d = malloc(sizeof(char *) * (ft_env_size(env) + 1));
	if (!env_2d)
	{
		ft_put_error("🍪: malloc failed\n");
		return (NULL);
	}
	r = 0;
	while (env)
	{
		env_2d[r++] = ft_strjoin2(ft_strdup2(env->key),
				ft_strjoin2(ft_strdup2("="), ft_strdup2(env->value)));
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
