/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:57:33 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/23 21:07:40 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

void	ft_env(t_env *env, char **cmd_2d, int *exit_status)
{
	if (cmd_2d[1])
	{
		ft_put_error("🍪: env: invalid argument\n");
		*exit_status = 127;
		return ;
	}
	ft_env_print(env);
	*exit_status = 0;
}
