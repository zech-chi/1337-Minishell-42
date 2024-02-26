/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:51:50 by ymomen            #+#    #+#             */
/*   Updated: 2024/02/24 12:48:55 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"

char	*ft_strchr_v2(const char *s, int c, char *del)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (*del = c ,(char *) s + i);
		i++;
	}
	if (s[i] == (char)c)
		return (*del = c ,(char *)s + i);
	return (NULL);
}