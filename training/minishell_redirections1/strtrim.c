/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:13:48 by zech-chi          #+#    #+#             */
/*   Updated: 2024/02/23 17:14:10 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"

static int	is_exist(char const *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	get_size(char const *s1, char const *set, size_t *l, size_t *r)
{
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	*l = 0;
	*r = s1_len - 1;
	while (*l < s1_len && is_exist(set, s1[*l]))
		*l += 1;
	if (*l == s1_len)
		return (0);
	while (*r >= 0 && is_exist(set, s1[*r]))
		*r -= 1;
	return (*r - *l + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size;
	size_t	i;
	size_t	left;
	size_t	right;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	size = get_size(s1, set, &left, &right);
	ptr = malloc(size + 1);
	if (ptr == NULL)
		return (NULL);
	if (size == 0)
	{
		ptr[0] = 0;
		return (ptr);
	}
	i = 0;
	while (left <= right)
		ptr[i++] = s1[left++];
	ptr[i] = 0;
	return (ptr);
}