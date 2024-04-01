/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infix_to_Postfix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:34:06 by ymomen            #+#    #+#             */
/*   Updated: 2024/03/31 19:47:41 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

t_lst   *from_infix_to_Postfix(t_lst *head)
{
    t_lst *postfix = NULL; 
    t_lst *stack = NULL; 
    t_lst *pop = NULL;         

    while (head) {
          
            if (head->type <= 0)
                lst_add_back(&postfix, post_new(head->value, head->type, head->prio, head->read));
            else if (head->type == OPEN_PARENTH)
                lst_add_back(&stack, post_new(head->value, head->type, head->prio, head->read));
             else if (head->type == CLOSE_PARENTH)
			 {
                while (stack && lastone(stack)->type != OPEN_PARENTH) {
                    pop = pop_last_1(&stack);
                    lst_add_back(&postfix, pop);
                }
                pop_last(&stack);
			 }
            else if (head->type > 0)
			{
                while (stack && lastone(stack)->type != OPEN_PARENTH && (lastone(stack)->prio < head->prio ||
                        (lastone(stack)->prio == head->prio && lastone(stack)->type == R_TO_L))) {
                    pop = pop_last_1(&stack);
                    lst_add_back(&postfix, pop);
                }
                lst_add_back(&stack, post_new(head->value, head->type, head->prio, head->read));
			}
        head = head->next;
    }
    while (stack) {
        pop = pop_last_1(&stack);
        lst_add_back(&postfix, pop);
    }
    return postfix;
}

t_tree *postfix_tree(t_lst *postfix)
{
    t_lst *stack;
    t_tree *tree;

    stack = NULL;
    while(postfix)
    {
        if (postfix->type == 0)
        {
            tree = new_node(postfix->value, postfix->prio, postfix->type, postfix->read);
            lst_add_back(&stack, lst_new(tree));
        }
        else
        {
            tree = new_node(postfix->value, postfix->prio ,postfix->type, postfix->read);
            tree->right = (t_tree *)(pop_last(&stack));
            if(!is_redarection(tree->type))
                tree->left = (t_tree *)(pop_last(&stack));
            lst_add_back(&stack, lst_new(tree));
        }
        postfix = postfix->next;
    }
    tree = pop_last(&stack);
    if(stack)
        return(printf("Error: Invalid expression\n"), NULL);
    update_tree(&tree);
    return (tree);
}
