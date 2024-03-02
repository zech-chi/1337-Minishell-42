/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:47:18 by zech-chi          #+#    #+#             */
/*   Updated: 2024/02/27 21:33:32 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_v2.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		ptr[i++] = s1[j++];
	j = 0;
	while (s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = 0;
	return (ptr);
}
