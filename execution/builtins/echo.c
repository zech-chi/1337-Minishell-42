/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:04:16 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/15 18:04:43 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

static int	ft_echo_valid_flag(char *flag)
{
	int	i;

	if (flag[0] != '-')
		return (0);
	i = 1;
	if (!flag[i])
		return (0);
	while (flag[i])
	{
		if (flag[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(char **cmd_2d)
{
	int	r;
	int	print_nl;

	print_nl = 1;
	r = 1;
	while (cmd_2d[r] && ft_echo_valid_flag(cmd_2d[r]))
	{
		print_nl = 0;
		r++;
	}
	while (cmd_2d[r])
	{
		printf("%s", cmd_2d[r++]);
		if (cmd_2d[r])
			printf(" ");
	}
	if (print_nl)
		printf("\n");
}
