/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:05:09 by zech-chi          #+#    #+#             */
/*   Updated: 2024/02/27 21:33:26 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_v2.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*ptr;

	len = ft_strlen(s1);
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	i = -1;
	while (++i < len)
		ptr[i] = s1[i];
	ptr[i] = '\0';
	return (ptr);
}
