/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infix_to_Postfix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:34:06 by ymomen            #+#    #+#             */
/*   Updated: 2024/03/25 16:06:39 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

t_lst *from_infix_to_Postfix(t_lst *head) {
    t_lst *postfix = NULL; 
    t_lst *stack = NULL; 
	t_lst *pop = NULL;         

    while (head) {
          
            if (head->type <= 0)
                lst_add_back(&postfix, lst_new(head->value));
            else if (head->type == OPEN_PARENTH)
                lst_add_back(&stack, lst_new(head->value));
             else if (head->type == CLOSE_PARENTH)
			 {
                while (stack && lastone(stack)->type != OPEN_PARENTH) {
                    pop = lst_new((void *)pop_last(&stack));
                    lst_add_back(&postfix, pop);
                }
                pop_last(&stack);
			 }
            else if (head->type > 0)
			{
                while (stack && lastone(stack)->type != OPEN_PARENTH && (lastone(stack)->prio < head->prio ||
                        (lastone(stack)->prio == head->prio && lastone(stack)->read == R_TO_L))) {
                    pop = lst_new((void *)pop_last(&stack));
                    lst_add_back(&postfix, pop);
                }
                lst_add_back(&stack, lst_new(head->value));
			}
        head = head->next;
    }
    while (stack) {
        pop = lst_new((void *)pop_last(&stack));
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
        if (postfix->type == 0)
        {
            tree = new_node(postfix->value);
            lst_add_back(&stack, lst_new(tree));
        }
        else
        {
            tree = new_node(postfix->value);
            tree->right = (t_tree *)(pop_last(&stack));
            tree->left = (t_tree *)(pop_last(&stack));
            lst_add_back(&stack, lst_new(tree));
        }
        postfix = postfix->next;
    }
    tree = pop_last(&stack);
    if (stack)
    {
        printf("here - 1\n") ;
        tree->right = pop_last(&stack);
        tree->left = pop_last(&stack);
    }
    return (tree);
}
