/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:34:39 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/25 20:09:08 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*cur_node;

	cur_node = *lst;
	if (cur_node == NULL)
	{
		*lst = new;
		return ;
	}
	while (cur_node->next)
		cur_node = cur_node->next;
	cur_node->next = new;
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*cur_node;

	cur_node = lst;
	if (cur_node == NULL)
		return (NULL);
	while (cur_node->next)
		cur_node = cur_node->next;
	return (cur_node);
}

int	ft_lstsize(t_list *lst)
{
	t_list	*cur_node;
	int		counter;

	cur_node = lst;
	counter = 0;
	while (cur_node)
	{
		counter++;
		cur_node = cur_node->next;
	}
	return (counter);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*cur_node;
	t_list	*nxt_node;

	if (!lst)
		return ;
	cur_node = *lst;
	while (cur_node)
	{
		nxt_node = cur_node->next;
		free(cur_node->content);
		free(cur_node);
		cur_node = nxt_node;
	}
	*lst = NULL;
}
