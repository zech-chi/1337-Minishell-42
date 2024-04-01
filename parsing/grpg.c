/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grpg.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 02:00:26 by ymomen            #+#    #+#             */
/*   Updated: 2024/04/01 17:45:08 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

 t_garbage *new_garbage(void *value)
 {
	 t_garbage *node;

	 node = (t_garbage *)malloc(sizeof(t_garbage));
	 if (!node)
		 return (NULL);
	 node->ptr = value;
	 node->next = NULL;
	 return (node);
 
 }

void add_to_grbg(t_garbage **head, void *value)
{
	t_garbage	*tmp;
	t_garbage	*node;

	node = new_garbage(value);
	if (!head || !node)
	{
		if (!node)
			write(2, "🍪: malloc error\n", 17);
		return ;    
	}
	if (!*head)
	{
		*head = node;
		(*head)->next = NULL;
		return ;
	}
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
		node->next = NULL;
		return ;
	}
}

void	clear_garbage(t_garbage *head)
{
	t_garbage	*node;

	if (!head)
		return ;
	node = head;
	while (head)
	{
		head = head ->next;
		free(node->ptr);
		free(node);
		node = head;
	}
}
