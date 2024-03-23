/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:49:47 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/23 22:28:36 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

static int	ft_is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ('0' <= str[i] && str[i] <= '9' && i == 0)
			return (0);
		if (
			!(
			('0' <= str[i] && str[i] <= '9')
			|| ('a' <= str[i] && str[i] <= 'z')
			|| ('A' <= str[i] && str[i] <= 'Z')
			|| str[i] == '_'
			)
		)
			return (0);
		i++;
	}
	return (1);
}

void	ft_unset(t_env **env, char **cmd_2d, int *exit_status)
{
	int	i;
	int	something_wrong;

	i = 1;
	something_wrong = 0;
	while (cmd_2d[i])
	{
		if (!(ft_is_valid_identifier(cmd_2d[i])))
		{
			ft_put_error("🍪: unset Error: ");
			ft_put_error(cmd_2d[i]);
			ft_put_error(" not a valid identifier\n");
			something_wrong = 1;
		}
		else
			ft_env_delete(env, cmd_2d[i]);
		i++;
	}
	if (something_wrong)
		*exit_status = 1;
	else
		*exit_status = 0;
}
