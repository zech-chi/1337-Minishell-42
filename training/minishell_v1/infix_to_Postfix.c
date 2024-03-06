/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infix_to_Postfix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:34:06 by ymomen            #+#    #+#             */
/*   Updated: 2024/03/07 00:42:28 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"

t_lst *from_infix_to_Postfix(t_lst *head) {
    t_lst *postfix = NULL; 
    t_lst *stack = NULL;          

    while (head) {
          
            if (head->type <= 0)
                lst_add_back(&postfix, lst_new(head->value));
            else if (head->type == OPEN_PARENTH)
                lst_add_back(&stack, lst_new(head->value));
             else if (head->type == CLOSE_PARENTH)
			 {
                while (stack && lastone(stack)->type != OPEN_PARENTH) {
                    t_lst *pop = lst_new((void *)pop_last(&stack));
                    lst_add_back(&postfix, pop);
                }
                pop_last(&stack);
			 }
            else if (head->type > 0)
			{
                while (stack && lastone(stack)->type != OPEN_PARENTH &&
                       (lastone(stack)->prio <= head->prio ||
                        (lastone(stack)->prio == head->prio && lastone(stack)->read == R_TO_L))) {
                    t_lst *pop = lst_new((void *)pop_last(&stack));
                    lst_add_back(&postfix, pop);
                }
                lst_add_back(&stack, lst_new(head->value));
			}
        head = head->next;
    }
    while (stack) {
        t_lst *pop = lst_new((void *)pop_last(&stack));
        lst_add_back(&postfix, pop);
    }

    return postfix;
}


t_tree *postfix_tree(t_lst *postfix)
{
	t_lst *stack = NULL;
	t_tree *tree = NULL;
	while(postfix)
	{
		if (postfix->prio == -1)
		{
			tree = new_node(postfix->value);
			lst_add_back(&stack, lst_new(tree));
		}
		else
		{
			tree = new_node(postfix->value);
			tree->right = (t_tree *)(pop_last(&stack));
			tree->left= (t_tree *)(pop_last(&stack));
			lst_add_back(&stack, lst_new(tree));
		}
		postfix = postfix->next;
	}
	tree = pop_last(&stack);
	return (tree);
}
