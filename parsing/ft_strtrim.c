/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 22:14:28 by ymomen            #+#    #+#             */
/*   Updated: 2024/04/05 05:18:09 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

char	*check(t_tool *tool)
{
	char	*newstr;

	newstr = (char *)malloc(1 * sizeof(char));
	if (!newstr)
		return (NULL);
	add_to_grbg(&tool->grbg, newstr);
	newstr[0] = '\0';
	return (newstr);
}

char	*ft_strtrim(const char *s1, const char *set, t_tool *tool)
{
	size_t	start;
	size_t	end;
	size_t	lenstr;
	char	*newstr;

	if (!s1)
		return (NULL);
	if (ft_strlen(s1) == 0)
		return (check(tool));
	if (ft_strlen(set) == 0 || !set)
		return (ft_strdup(s1, tool));
	end = ft_strlen(s1) - 1;
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end]))
		end--;
	lenstr = end - start + 1;
	newstr = (char *)malloc((lenstr + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	add_to_grbg(&tool->grbg, newstr);
	ft_strlcpy(newstr, &s1[start], lenstr + 1);
	return (newstr);
}
