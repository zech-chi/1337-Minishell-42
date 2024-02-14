/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:47:18 by zech-chi          #+#    #+#             */
/*   Updated: 2024/02/14 11:47:36 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*ptr;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	ptr = malloc(size + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	if (size > 0)
	{
		j = 0;
		while (s1[j])
			ptr[i++] = s1[j++];
		j = 0;
		while (s2[j])
			ptr[i++] = s2[j++];
	}
	ptr[i] = 0;
	return (ptr);
}
