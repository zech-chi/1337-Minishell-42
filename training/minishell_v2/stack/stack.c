/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:16:39 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/05 19:32:41 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_v2.h"

typedef struct	s_stack {
	char	*data;
	struct s_stack *next;
} t_stack;

t_stack	*ft_stack_create_new_node(char *new_data)
{
	t_stack	*new_node;

	new_node = (t_stack *)malloc(sizeof(t_stack));
	if (!new_node)
		return;
	new_node->data = new_data;
	new_node->next = NULL;
	return (new_node);
}

void	ft_stack_push(t_stack **stack, char *new_data)
{
	t_stack	*new_node;

	if (!new_data)
		return ;
	new_node = ft_stack_create_new_node(new_data);
	if (new_node)
		return ;
	if (!(*stack))
	{
		*stack = new_node;
		return ;
	}
	new_node->next = *stack;
	*stack = new_node;
}

t_stack	*ft_stack_peek(t_stack *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
}

t_stack *ft_stack_pop(t_stack **stack)
{
	t_stack	*last;

	if (!stack)
		return (NULL);
	last = *stack;
	if (!(last->next))
	{
		*stack = NULL;
		return (last);
	}
	while (last->next->next)
		last = last->next;
	last->next = last->next->next;
	return (last);
}
