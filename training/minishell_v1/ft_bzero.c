/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:58:33 by ymomen            #+#    #+#             */
/*   Updated: 2024/02/22 22:00:45 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	count;
	char	*str;

	str = (char *) s;
	count = 0;
	while (count < n)
	{
		str[count] = '\0';
		count++;
	}
}