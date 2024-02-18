/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:39:10 by zech-chi          #+#    #+#             */
/*   Updated: 2024/02/16 12:13:57 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"

void	ft_pwd_print(t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->key, "PWD"))
		{
			printf("%s\n", env->value);
			return ;
		}
		env = env->next;
	}
	printf("NULL\n");
}