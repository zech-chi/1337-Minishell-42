/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oltils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 00:21:31 by ymomen            #+#    #+#             */
/*   Updated: 2024/04/03 15:15:42 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

int	is_delimter(char c)
{
	if (c == '|' || c == '&' || c == '>' || c == '<' || c == '(' || c == ')')
	{
		if (c == '>')
			return (REDIRECTION);
		else if (c == '<')
			return (INPUT);
		else if (c == '|')
			return (PIPE);
		else if (c == '&')
			return (SINGL_AND);
		else if (c == '(')
			return (OPEN_PARENTH);
		else if (c == ')')
			return (CLOSE_PARENTH);
	}
	return (0);
}

char	*ft_monstrdup(const char *s1, size_t size, t_tool *tool)
{
	char		*dup;
	size_t		i;

	i = 0;
	dup = (char *) malloc(size + 1 * sizeof(char));
	if (!dup)
		return (NULL);
	add_to_grbg(&tool->grbg, dup);
	while (i < size)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s2[i] - s1[i]);
		i++;
	}
	return (0);
}

void	trime(t_lst *head, t_tool *tool)
{
	char	*arr;

	if (!head)
		return ;
	while (head)
	{
		arr = head->value;
		head->value = ft_strtrim(arr, " ", tool);
		head = head->next;
	}
}

int	is_redarection(int type)
{
	if (type == REDIRECTION || type == INPUT || type == APPEND_REDIRECTION
		|| type == HERE_DOC)
		return (1);
	return (0);
}
