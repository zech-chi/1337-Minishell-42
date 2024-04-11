/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:20:33 by ymomen            #+#    #+#             */
/*   Updated: 2024/04/11 16:11:41 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

static int	contdel(char const *s, char c)
{
	int	i;
	int	rst;

	i = 0;
	rst = 0;
	while (s[i])
	{
		if ((s[i + 1] == c && s[i] != c) || (s[i + 1] == '\0' && s[i] != c))
			rst++;
		i++;
	}
	return (rst);
}

static char	**fullandfree(char **ptr, const char *s, char c, t_tool *tool)
{
	int	start;
	int	end;
	int	i;
	int	count_words;

	start = 0;
	end = 0;
	i = 0;
	count_words = contdel(s, c);
	while (s[start] && count_words > i)
	{
		while (s[end] && s[end] == c)
			end++;
		start = end;
		while (s[end] != '\0' && s[end] != c)
			end++;
		ptr[i] = ft_monstrdup(&s[start], (end - start), tool);
		if (!ptr[i])
			return (NULL);
		start = end;
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}

char	**ft_split(char const *s, char c, t_tool *tool)
{
	int		count_words;
	char	**ptr;

	if (!s)
		return (NULL);
	count_words = contdel(s, c);
	ptr = (char **) malloc(sizeof(char *) * (count_words + 1));
	if (!ptr)
		return (NULL);
	add_to_grbg(&tool->grbg, ptr);
	return (fullandfree(ptr, s, c, tool));
}
