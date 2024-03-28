/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 20:10:54 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/28 20:10:56 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

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
