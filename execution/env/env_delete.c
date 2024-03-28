/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 20:06:08 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/28 20:06:14 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

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
		return (free(prev->key), free(prev->value), free(prev));
	}
	cur = prev->next;
	while (cur)
	{
		if (!ft_strcmp2(key, cur->key))
		{
			prev->next = cur->next;
			return (free(cur->key), free(cur->value), free(cur));
		}
		cur = cur->next;
		prev = prev->next;
	}
}
