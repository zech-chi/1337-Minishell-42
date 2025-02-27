/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infix_to_Postfix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:34:06 by ymomen            #+#    #+#             */
/*   Updated: 2024/04/11 15:51:11 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

void	postfixcontu(t_lst **head, t_lst **postfix, t_lst **stack, t_tool *tool)
{
	t_lst	*pop;

	if ((*head)->type == CLOSE_PARENTH)
	{
		while (stack && *stack && lastone(*stack)->type != OPEN_PARENTH)
		{
			pop = pop_last_1(stack);
			lst_add_back(postfix, pop);
		}
		pop_last_1(stack);
	}
	else if ((*head)->type > 0)
	{
		while (stack && *stack && lastone(*stack)->type != OPEN_PARENTH
			&& (lastone(*stack)->prio < (*head)->prio
				|| (lastone(*stack)->prio == (*head)->prio
					&& lastone(*stack)->read == R_TO_L)))
		{
			pop = pop_last_1(stack);
			lst_add_back(postfix, pop);
		}
		lst_add_back(stack, post_new((*head), tool));
	}
}

t_lst	*from_infix_to_postfix(t_lst *head, t_tool *tool)
{
	t_lst	*postfix;
	t_lst	*stack;
	t_lst	*pop;

	postfix = NULL;
	stack = NULL;
	while (head)
	{
		if (head->type <= 0)
			lst_add_back(&postfix, post_new(head, tool));
		else if (head->type == OPEN_PARENTH)
			lst_add_back(&stack, post_new(head, tool));
		else
			postfixcontu(&head, &postfix, &stack, tool);
		head = head->next;
	}
	while (stack)
	{
		pop = pop_last_1(&stack);
		lst_add_back(&postfix, pop);
	}
	return (postfix);
}

t_tree	*postfix_tree(t_lst *postfix, t_tool *tool)
{
	t_lst	*stack;
	t_tree	*tree;

	stack = NULL;
	while (postfix)
	{
		if (postfix->type <= 0)
		{
			tree = new_node(postfix->value, postfix->prio, postfix->type, tool);
			lst_add_back(&stack, lst_new(tree, tool));
		}
		else
		{
			tree = new_node(postfix->value, postfix->prio, postfix->type, tool);
			tree->right = (t_tree *)(pop_last(&stack));
			if (!is_redarection(tree->type))
				tree->left = (t_tree *)(pop_last(&stack));
			lst_add_back(&stack, lst_new(tree, tool));
		}
		postfix = postfix->next;
	}
	tree = pop_last(&stack);
	if (stack)
		return (printf("Error: Invalid expression\n"), NULL);
	return (tree);
}
