/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:49:47 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/16 17:58:41 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

int	ft_unset(t_env **env, char **splited_prompt)
{
	int	i;

	i = 1;
	while (splited_prompt[i])
		ft_env_delete(env, splited_prompt[i++]);
	return (0);
}
