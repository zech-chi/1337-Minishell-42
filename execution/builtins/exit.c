/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 00:50:36 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/23 21:21:55 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

static void	ft_print_error(char *s, int ex)
{
	if (!s)
		return ;
	printf("exit\n");
	write(2, s, ft_strlen2(s));
	if (ex)
		exit(255);
}

static int	ft_non_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(('0' <= str[i] && str[i] <= '9')
				|| str[i] == '-' || str[i] == '+'))
			return (1);
		i++;
	}
	return (0);
}

static int	ft_get_modulo(long long ll)
{
	if (ll >= 0)
		return (ll % 256);
	return (ll - (ll / 256) * 256 + 256);
}

static void	ft_atoll(char *str)
{
	long long	ll;
	int			i;
	int			signe;

	ll = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	signe = 1 - 2 * (str[i] == '-');
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i] || str[i] == '-' || str[i] == '+')
		ft_print_error("🍪: exit: invalid argument\n", 1);
	while ('0' <= str[i] && str[i] <= '9')
	{
		if (ll > LLONG_MAX / 10 || (ll == LLONG_MAX / 10
				&& ((signe == 1 && str[i] - '0' > 7)
					|| (signe == -1 && str[i] - '0' > 8))))
			ft_print_error("🍪: exit: invalid argument\n", 1);
		ll = ll * 10 + str[i++] - '0';
	}
	if (str[i])
		ft_print_error("🍪: exit: invalid argument\n", 1);
	printf("exit\n");
	exit(ft_get_modulo(ll * signe));
}

void	ft_exit(char **cmd_2d, int *exit_status)
{
	if (!cmd_2d[1])
	{
		printf("exit\n");
		exit(0);
	}
	else if (ft_non_numeric(cmd_2d[1]))
		ft_print_error("🍪: exit: invalid argument\n", 1);
	else if (cmd_2d[2])
	{
		ft_print_error("🍪: exit: invalid argument\n", 0);
		*exit_status = 255;
	}
	else
		ft_atoll(cmd_2d[1]);
}
