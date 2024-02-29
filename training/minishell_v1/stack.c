/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:39:11 by ymomen            #+#    #+#             */
/*   Updated: 2024/02/28 22:37:09 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"

t_stack *stack_new(void *str)
{
	t_stack *node;
	
	if (!str || check_arr(str) == 0)
		return (NULL);
	node = (t_stack *) malloc(sizeof(t_stack));
	if (!node)
		return (NULL);
	node->value  = str;
	node->next = NULL;
	return (node);
}
void stack_add_back(t_stack **head, t_stack *node)
{
	t_stack * tmp;
	if (!head || !node)
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
		node->next = NULL;
	return ;	
	}
}
int size_stack(t_stack **head)
{
	t_stack *tmp;
	int i;

	if (!head || !*head)
		return (0);
	i = 0;
	tmp = *head;
	while(tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
void stack_clear(t_stack *head)
{
	t_stack *node;
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
void *pop_stack(t_stack **stack)
{
	void  *ptr = NULL;
	t_stack *tmp;
	t_stack *prv;
	if (!stack || !*stack)
		return (NULL);
	
	tmp = *stack;
	if (!(*stack)->next)
	{
		ptr = (*stack)->value;
		free(*stack);
		*stack= NULL; 
		return(ptr);
	}
	while((*stack)->next)
	{
		prv = *stack;
		*stack = (*stack)->next;
	}
	ptr = (*stack)->value;
		free(*stack);
		*stack= NULL;
		prv->next = NULL;
	*stack = tmp;
	return (ptr);
}

void	ft_stackadd_front(t_stack **stack, t_stack *new)
{
	new->next = *stack;
	*stack = new;
}
t_stack *lastonestack(t_stack *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return(head);
}