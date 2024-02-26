/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 23:32:33 by ymomen            #+#    #+#             */
/*   Updated: 2024/02/26 00:05:30 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"

int is_delimter(char c)
{
	if (c == '|' || c == '&'|| c == '>' || c == '<' || c == '(' || c == ')')
		{
			if (c == '>')
				return (REDIRECTION);
			else if (c == '<')
				return (LESS_THAN);
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
void is_quot_open(int *pass, char command)
{
	if (command == '\'' && *pass == 0)
		*pass = 1;
	else if (command == '\'' && *pass == 1)
		*pass = 0;
	else if (command == '"' && *pass == 0)
		*pass = 2;
	else if (command == '"' && *pass == 2)
		*pass = 0;
}

t_lst *tokens_lst(char *command)
{
	int end;
	t_lst *node = NULL;
	int pass = 0;
	int i = 0;
	while(command[i])
	{
		is_quot_open(&pass ,command[i]);
		if (command[i] && (is_delimter(command[i]) > 0) && pass == 0)
		{
			if ((is_delimter(command[i + 1]) > 0)  && ((is_delimter(command[i + 1]) < 5) && (is_delimter(command[i]) < 5)))
			{
				lst_add_back(&node, lst_new(ft_monstrdup(&command[i], 2)));
				i++;
			}
			else
				lst_add_back(&node, lst_new(ft_monstrdup(&command[i], 1)));
		}
		else
		{
			end = i;
			while(command[end] && (pass || !is_delimter(command[end])))
			{
				end++;
				is_quot_open(&pass ,command[end]);
			}
			if (end != i)
			{
				lst_add_back(&node, lst_new(ft_monstrdup(&command[i], end - i)));
				i = end -1;
			}
		}
		i++;
	}
	return (node);
}

char check_arr(char *arr)
{
	int i = 0;
	while (arr[i])
	{
		if (arr[i] != ' ')
			return (1);
		i++;
	}
	return(0);
}

char **lst_to_arr(t_lst *head)
{
	int size = size_lst(head);
	char **arr;
	int i = 0;
	t_lst *node;

	node = head;
	arr= (char **) malloc(sizeof (char *) * (size + 1));
	if (!arr)
		return (NULL);
	while (node && i < size)
	{
		arr[i] = ft_strtrim(node->value, " ");
		 if (check_arr(arr[i]))
			i++;
		else
			free(arr[i]);	
		node = node->next;
	}
	arr[i] = NULL;
	lst_clear(head);
	return (arr);
}
