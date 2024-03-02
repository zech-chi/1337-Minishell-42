/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:08:34 by zech-chi          #+#    #+#             */
/*   Updated: 2024/02/21 15:00:45 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"

int ft_unset(t_env **env, char **splited_prompt)
{
	int i;

	i = 1;
	while (splited_prompt[i])
		ft_env_delete(env, splited_prompt[i++]);
	return (0);
}
