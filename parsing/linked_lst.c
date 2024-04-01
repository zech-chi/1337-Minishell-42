/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:39:11 by ymomen            #+#    #+#             */
/*   Updated: 2024/04/01 14:45:07 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

t_lst	*lst_new(void *str, t_tool *tool)
{
	t_lst			*node;
	static t_lst	*prev;

	if (!str)
		return (NULL);
	node = (t_lst *) malloc(sizeof(t_lst));
	if (!node)
		return (NULL);
	add_to_grbg(&tool->grbg, node);
	node->value = str;
	init_type(&node);
	prev = node;
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
		*stack = NULL;
		return (ptr);
	}
	while ((*stack)->next)
	{
		prv = *stack;
		*stack = (*stack)->next;
	}
	ptr = (*stack)->value;
	*stack = NULL;
	prv->next = NULL;
	*stack = tmp;
	return (ptr);
}
t_lst	*pop_last_1(t_lst **stack)
{
	t_lst	*ptr;
	t_lst	*tmp;
	t_lst	*prv;

	if (!stack || !*stack)
		return (NULL);
	tmp = *stack;
	if (!(*stack)->next)
	{
		ptr = (*stack);
		*stack = NULL;
		return (ptr);
	}
	while ((*stack)->next)
	{
		prv = *stack;
		*stack = (*stack)->next;
	}
	ptr = (*stack);
	*stack = NULL;
	prv->next = NULL;
	*stack = tmp;
	return (ptr);
}
t_lst	*post_new(void *str,int type, int prio, t_tool *tool)
{
	t_lst			*node;
	static t_lst	*prev;

	if (!str)
		return (NULL);
	node = (t_lst *) malloc(sizeof(t_lst));
	if (!node)
		return (NULL);
	add_to_grbg(&tool->grbg, node);
	node->value = str;
	node->prio = prio;
	node->type = type;
	prev = node;
	node->next = NULL;
	return (node);
}
