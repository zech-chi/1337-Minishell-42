/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 01:12:51 by zech-chi          #+#    #+#             */
/*   Updated: 2024/04/07 18:26:57 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	signe;
	int	i;

	res = 0;
	signe = 1;
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (str[i] && '0' <= str[i] && str[i] <= '9')
		res = 10 * res + str[i++] - '0';
	return (signe * res);
}
