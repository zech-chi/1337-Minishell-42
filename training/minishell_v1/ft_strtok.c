/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 23:32:33 by ymomen            #+#    #+#             */
/*   Updated: 2024/02/22 22:00:11 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"

char	*ft_strtok(char *str, char	*delim, char *del)
{
	static char	*p;
	char		*start;

	if (str != NULL)
		p = str;
	else if (p == NULL || !*p)
		return (NULL);
	start = p;
	while (*p && ft_strchr(delim, *p, del) == NULL)
		p++;
	if ((*(p + 1) == '|' && *del == '|') || (*(p + 1) == '&' && *del == '&')
		||(*(p + 1) == '>' && *del == '>') || (*(p + 1) == '<' && *del == '<'))
	{
		if (*del == '|')
			*(del + 1) = '|';
		else if (*del == '&')
			*(del+1) = '&';
		else if (*del == '>')
			*(del+1) = '>';
		else
			*(del+1) = '<';
		*p++ = '\0';
	}
	if (*p)
		*p++ = '\0';
	return (start);
}
