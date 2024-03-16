/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:39:39 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/16 17:42:30 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

int	ft_export(t_env **env, char **splited_prompt)
{
	int		i;
	char	**one_by_one;

	i = 0;
	while (splited_prompt[++i])
	{
		one_by_one = ft_split2(splited_prompt[i], '=');
		if (!one_by_one || !one_by_one[0] || !one_by_one[1])
			continue ;
		if (ft_env_update(env, one_by_one[0], one_by_one[1]))
			ft_env_add(env, one_by_one[0], one_by_one[1]);
	}
	return (0);
}
