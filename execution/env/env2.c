/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:49:44 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/26 22:26:27 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

int	ft_env_update(t_env **env, char *key, char *newval, int append_mod)
{
	t_env	*node;

	node = *env;
	while (node)
	{
		if (!ft_strcmp2(node->key, key))
		{
			if (append_mod)
				node->value = ft_strjoin2(node->value, newval);
			else
			{
				free(node->value);
				node->value = newval;
			}
			free(key);
			return (0);
		}
		node = node->next;
	}
	return (1);
}

// add new key and value in env 
// return 0 if all good, -1 otherwise
int	ft_env_add(t_env **env, char *key, char *value, int visible)
{
	t_env	*new;
	t_env	*last;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (-1);
	new->key = key;
	new->value = value;
	new->next = NULL;
	new->visible = visible;
	last = *env;
	if (!last)
		return (*env = new, 0);
	while (last->next)
		last = last->next;
	last->next = new;
	return (0);
}

// must free here!!!
void	ft_env_delete(t_env **env, char *key)
{
	t_env	*prev;
	t_env	*cur;

	if (!env || !(*env))
		return ;
	prev = *env;
	if (!ft_strcmp2(key, prev->key))
	{
		(*env) = prev->next;
		free(prev->key);
		free(prev->value);
		free(prev);
		return ;
	}
	cur = prev->next;
	while (cur)
	{
		if (!ft_strcmp2(key, cur->key))
		{
			prev->next = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return ;
		}
		cur = cur->next;
		prev = prev->next;
	}
}

// search for key and return its value
// for example if key == "USER" it returns "zech-chi"
// if key not in env it returns NULL
char	*ft_env_search(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp2(env->key, key))
			return (ft_strdup2(env->value));
		env = env->next;
	}
	return (NULL);
}

// print env like you typing env in terminal
void	ft_env_print(t_env *env)
{
	while (env)
	{
		if (env->visible)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
