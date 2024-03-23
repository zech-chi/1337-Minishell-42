/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:49:18 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/15 17:47:50 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

static int	len_of_number(long long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		len += 1;
	}
	while (n)
	{
		len += 1;
		n /= 10;
	}
	return (len);
}

static char	*fill(char *ptr, long long ln, int size)
{
	int	i;

	if (ln == 0)
	{
		ptr[0] = '0';
		ptr[1] = 0;
		return (ptr);
	}
	if (ln < 0)
	{
		ptr[0] = '-';
		ln *= -1;
	}
	i = size - 1;
	while (ln)
	{
		ptr[i] = '0' + ln % 10;
		ln /= 10;
		i--;
	}
	ptr[size] = 0;
	return (ptr);
}

char	*ft_itoa2(int n)
{
	int			size;
	long long	ln;
	char		*ptr;

	ln = (long long)n;
	size = len_of_number(ln);
	ptr = malloc(size + 1);
	if (ptr == NULL)
		return (NULL);
	fill(ptr, ln, size);
	return (ptr);
}
