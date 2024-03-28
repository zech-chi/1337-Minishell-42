/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 20:07:13 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/28 20:07:17 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

void	ft_env_print(t_env *env)
{
	while (env)
	{
		if (env->visible)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
