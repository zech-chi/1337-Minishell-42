/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oltils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 00:21:31 by ymomen            #+#    #+#             */
/*   Updated: 2024/03/02 17:44:36 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"

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

char	*ft_monstrdup(const char *s1, size_t size)
{
	char		*dup;
	size_t		i;

	i = 0;
	dup = (char *) malloc(size + 1 * sizeof(char));
	if (!dup)
		return (NULL);
	while (i < size)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	check_arr(char *arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (arr[i] != ' ')
			return (1);
		i++;
	}
	return (0);
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

void	trime(t_lst *head)
{
	char	*arr;

	if (!head)
		return ;
	while (head)
	{
		arr = head->value;
		head->value = ft_strtrim(arr, " ");
		free(arr);
		head = head->next;
	}
}
