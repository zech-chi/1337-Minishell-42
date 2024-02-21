/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:55:47 by zech-chi          #+#    #+#             */
/*   Updated: 2024/02/21 15:17:47 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"

// add new key and value in env 
// return 0 if all good, -1 otherwise
int	ft_env_add(t_env **env, char *key, char *value)
{
	t_env	*new;
	t_env	*last;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (-1);
	new->key = key;
	new->value = value;
	new->next = NULL;
	last = *env;
	if (!last)
		return (*env = new, 0);
	while (last->next)
		last = last->next;
	last->next = new;
	return (0);
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

// print env like you typing env in terminal
void	ft_env_print(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

// creat linked list env
// return env linked list on success, NULL otherwise
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
		splited_row = ft_split(ev[r], EQUAL);
		if (!splited_row)
			return (NULL); // I should clear env !!!!
		c = 1;
		value = NULL;
		while (splited_row[c])
		{
			if (c == 1)
				value = ft_strjoin(value, splited_row[c]);
			else
				value = ft_strjoin(value, ft_strjoin("=", splited_row[c]));
			c++;
		}
		ft_env_add(&env, splited_row[0], value);
		free(splited_row);
	}
	return (env);
}


// search for key and return its value
// for example if key == "USER" it returns "zech-chi"
// if key not in env it returns NULL
char	*ft_env_search(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
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
		env_2d[r++] = ft_strjoin(ft_strdup(env->key), ft_strjoin("=", ft_strdup(env->value)));
		env = env->next;
	}
	env_2d[r] = NULL;
	return (env_2d);
}

int	ft_env_update(t_env **env, char *key, char *newval)
{
	t_env	*node;

	node = *env;
	while (node)
	{
		if (!ft_strcmp(node->key, key))
		{
			node->value = newval;
			return (0);
		}
		node = node->next;
	}
	return (1);
}

void	ft_env_delete(t_env **env, char *key)
{
	t_env	*prev;
	t_env	*cur;

	if (!env || !(*env))
		return ;
	prev = *env;
	if (!ft_strcmp(key, prev->key))
	{
		(*env) = prev->next;
		return ;
	}
	cur = prev->next;
	while (cur)
	{
		if (!ft_strcmp(key, cur->key))
		{
			prev->next = cur->next;
			return ; // must free here!!!
		}
		cur = cur->next;
		prev = prev->next;
	}
}

//int main(int ac, char **av, char **ev)
//{
//	t_env *env;

//	(void)(ac);
//	(void)(av);
//	env = ft_env_create(ev);
//	ft_env_print(env);
//	return (SUCCESS);
//}
