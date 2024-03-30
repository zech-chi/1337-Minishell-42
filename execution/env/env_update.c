/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 20:04:50 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/29 03:54:18 by zech-chi         ###   ########.fr       */
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
			node->visible = 1;
			free(key);
			key = NULL;
			return (0);
		}
		node = node->next;
	}
	return (1);
}
