/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:39:11 by ymomen            #+#    #+#             */
/*   Updated: 2024/02/25 23:09:38 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"

t_lst *lst_new(char *str)
{
	t_lst *node;
	
	if (!str)
		return (NULL);
	node = (t_lst *) malloc(sizeof(t_lst));
	if (!node)
		return (NULL);
	node->value  = str;
	node->next = NULL;
	return (node);
}
void lst_add_back(t_lst **head, t_lst *node)
{
	t_lst * tmp;
	if (!head | !node)
		return ;
	if (!*head)
	{
		*head = node;
		return;
	}
	else
	{
		tmp = *head;
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	return ;	
	}
}
int size_lst(t_lst *head)
{
	t_lst *tmp;
	int i;

	if (!head)
		return (0);
	i = 0;
	tmp = head;
	while(tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
void lst_clear(t_lst *head)
{
	t_lst *node;
	if (!head)
		return ;
	node = head;
	while(head)
	{
		head = head ->next;
		free(node->value);
		free(node);
		node = head;
	}
}