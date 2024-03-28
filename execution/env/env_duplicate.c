/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_duplicate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 20:08:41 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/28 20:08:43 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

t_env	*ft_env_duplicate(t_env *env)
{
	t_env	*env_dup;

	env_dup = NULL;
	while (env)
	{
		ft_env_add(&env_dup, ft_strdup2(env->key),
			ft_strdup2(env->value), env->visible);
		env = env->next;
	}
	return (env_dup);
}
