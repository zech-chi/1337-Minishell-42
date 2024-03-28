/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 20:05:17 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/28 20:05:27 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

int	ft_env_add(t_env **env, char *key, char *value, int visible)
{
	t_env	*new;
	t_env	*last;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (ft_put_error("🍪: malloc failed\n"), -1);
	new->key = key;
	new->value = value;
	new->next = NULL;
	new->visible = visible;
	last = *env;
	if (!last)
		return (*env = new, 0);
	if (ft_strcmp2(new->key, last->key) < 0)
		return (new->next = *env, *env = new, 0);
	while (last && last->next)
	{
		if (ft_strcmp2(new->key, last->next->key) < 0)
			return (new->next = last->next, last->next = new, 0);
		last = last->next;
	}
	last->next = new;
	return (0);
}
