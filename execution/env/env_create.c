/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 20:03:15 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/28 20:13:35 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

static char	*ft_get_join_value(char **splited_row)
{
	char	*value;
	int		c;

	value = NULL;
	c = 0;
	while (splited_row[++c])
	{
		if (c == 1)
			value = ft_strjoin2(value, ft_strdup2(splited_row[c]));
		else
			value = ft_strjoin2(value,
					ft_strjoin2(ft_strdup2("="),
						ft_strdup2(splited_row[c])));
	}
	return (value);
}

static int	ft_add_item(t_env **env, char *key, char *value, int visible)
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

t_env	*ft_env_create(char **ev)
{
	t_env	*env;
	char	**splited_row;
	int		r;
	char	*key;
	char	*value;

	r = -1;
	env = NULL;
	while (ev[++r])
	{
		splited_row = ft_split2(ev[r], EQUAL);
		if (!splited_row)
			return (NULL);
		key = ft_strdup2(splited_row[0]);
		value = ft_get_join_value(splited_row);
		ft_add_item(&env, key, value, 1);
		ft_free_2d_char(splited_row);
	}
	ft_env_delete(&env, "OLDPWD");
	ft_env_add(&env, ft_strdup2("OLDPWD"), ft_strdup2(""), 0);
	return (env);
}
