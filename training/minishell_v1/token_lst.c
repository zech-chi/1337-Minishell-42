/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 23:32:33 by ymomen            #+#    #+#             */
/*   Updated: 2024/02/29 23:33:23 by ymomen           ###   ########.fr       */
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
void is_parc_open(int *parc, char command, int pass)
{
	if (pass)
		return ;
	else
	{
		if (command == '(')
		*parc += 1;
	else if (command == ')' && *parc)
		*parc -= 1;
	else if (command == ')')
		*parc = 451454545;
	}
}

void trime(t_lst *head)
{
	if (!head)
		return;

	char *arr;
	while(head)
	{
		arr = head->value;
		head->value = ft_strtrim(arr, " ");
		free(arr);
		head = head->next;
	}
}

t_lst *tokens_lst(char *command)
{
	int end;
	t_lst *node = NULL;
	int pass = 0;
	int parc = 0;
	int i = 0;
	while(command[i])
	{
		is_quot_open(&pass ,command[i]);
		is_parc_open(&parc, command[i], pass);
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
	if (parc)
	{
		write(2, "error!\n", 8);
		return (NULL);
	}
	return (trime(node), node);
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
