/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:39:11 by ymomen            #+#    #+#             */
/*   Updated: 2024/03/19 00:00:28 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

t_lst	*lst_new(void *str)
{
	t_lst	*node;

	if (!str)
		return (NULL);
	node = (t_lst *) malloc(sizeof(t_lst));
	if (!node)
	{
		free(str);
		return (NULL);
	}
	node->value = str;
	is_operateur(&node);
	node->next = NULL;
	return (node);
}

void	lst_add_back(t_lst **head, t_lst *node)
{
	t_lst	*tmp;

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

int	size_lst(t_lst **head)
{
	t_lst	*tmp;
	int		i;

	if (!head || !*head)
		return (0);
	i = 0;
	tmp = *head;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	lst_clear(t_lst *head)
{
	t_lst	*node;

	if (!head)
		return ;
	node = head;
	while (head)
	{
		head = head ->next;
		free(node->value);
		free(node);
		node = head;
	}
}

void	*pop_last(t_lst **stack)
{
	void	*ptr;
	t_lst	*tmp;
	t_lst	*prv;

	if (!stack || !*stack)
		return (NULL);
	tmp = *stack;
	if (!(*stack)->next)
	{
		ptr = (*stack)->value;
		free(*stack);
		*stack = NULL;
		return (ptr);
	}
	while ((*stack)->next)
	{
		prv = *stack;
		*stack = (*stack)->next;
	}
	ptr = (*stack)->value;
	free(*stack);
	*stack = NULL;
	prv->next = NULL;
	*stack = tmp;
	return (ptr);
}
void	 lst_add_front(t_lst **lst, t_lst *new)
{
	t_lst	*tmp;
	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		(*lst)->next = NULL;
		return ;
	}
	tmp = *lst;
	new->next = tmp;
	*lst = new;
}

t_lst *lst_pop(t_lst **lst)
{
	t_lst	*top;

	top = *lst;
	*lst = (*lst)->next;
	return (*lst);
}