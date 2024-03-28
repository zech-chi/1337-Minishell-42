/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 20:06:37 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/28 20:06:44 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

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
