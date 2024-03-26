/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 02:41:11 by ymomen            #+#    #+#             */
/*   Updated: 2024/03/26 01:54:30 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

static size_t	totalen(const char *s1, const char *s2)
{
	size_t	s1l;
	size_t	s2l;

	s1l = ft_strlen(s1);
	s2l = ft_strlen(s2);
	return (s1l + s2l);
}

void	free_it(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	lentot;
	size_t	i;
	size_t	count;
	char	*newstr;

	if (!s1 || !s2)
		return (NULL);
	lentot = totalen(s1, s2);
	i = 0;
	count = 0;
	newstr = (char *) malloc(lentot + 1);
	if (!newstr)
		return (NULL);
	while (s1[count] && lentot > count)
	{
		newstr[count] = s1[count];
		count++;
	}
	while (s2[i] && lentot > (count + i))
	{
		newstr[count + i] = s2[i];
		i++;
	}
	newstr[count + i] = '\0';
	return (free_it((char *)s1, (char *)s2), newstr);
}
