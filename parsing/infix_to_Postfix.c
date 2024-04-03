/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infix_to_Postfix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:34:06 by ymomen            #+#    #+#             */
/*   Updated: 2024/04/03 11:03:59 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

t_lst   *from_infix_to_Postfix(t_lst *head, t_tool *tool)
{
    t_lst *postfix = NULL; 
    t_lst *stack = NULL; 
    t_lst *pop = NULL;  

    while (head) {
          
            if (head->type <= 0)
                lst_add_back(&postfix, post_new(head, tool));
            else if (head->type == OPEN_PARENTH)
                lst_add_back(&stack, post_new(head, tool));
             else if (head->type == CLOSE_PARENTH)
			 {
                while (stack && lastone(stack)->type != OPEN_PARENTH) {
                    pop = pop_last_1(&stack);
                    lst_add_back(&postfix, pop);
                }
                pop_last_1(&stack);
			 }
            else if (head->type > 0)
			{
                while (stack && lastone(stack)->type != OPEN_PARENTH && (lastone(stack)->prio < head->prio ||
                        (lastone(stack)->prio == head->prio && lastone(stack)->read == R_TO_L ))) {
                    pop = pop_last_1(&stack);
                    lst_add_back(&postfix, pop);
                }
                lst_add_back(&stack, post_new(head, tool));
			}
        head = head->next;
    }
    while (stack) {
        pop = pop_last_1(&stack);
        lst_add_back(&postfix, pop);
    }
    return (postfix);
       
}

t_tree *postfix_tree(t_lst *postfix, t_tool *tool)
{
    t_lst *stack;
    t_tree *tree;

    stack = NULL;
    while(postfix)
    {
        if (postfix->type <= 0)
        {
            tree = new_node(postfix->value, postfix->prio, postfix->type, tool);
            lst_add_back(&stack, lst_new(tree, tool));
        }
        else
        {
            tree = new_node(postfix->value, postfix->prio ,postfix->type, tool);
            tree->right = (t_tree *)(pop_last(&stack));
            if(!is_redarection(tree->type))
                tree->left = (t_tree *)(pop_last(&stack));
            lst_add_back(&stack, lst_new(tree, tool));
        }
        postfix = postfix->next;
    }
    tree = pop_last(&stack);
    if(stack)
    {
        return(printf("Error: Invalid expression\n"), NULL);
    }
    update_tree(&tree, tool);
    return (tree);
}

// int lst_get_size(t_lst *head) {
//   int size = 0;
//   while (head) {
//     head = head->next;
//     size++;
//   }
//   return size;
// }
// t_tree *lst_peek(t_lst *head) {
//   if (!head) {
//     return NULL;  // List is empty
//   }
//   return ((t_tree *)head->value);  // Return the first element (head)
// }
// t_tree *postfix_tree(t_lst *postfix, t_tool *tool) {
//     t_lst *stack;  // Existing stack for postfix elements
//     t_lst *subtree_stack;  // New stack for subtrees rooted at &&
//     t_tree *tree;

//     stack = NULL;
//     subtree_stack = NULL;
//     while (postfix) {
//         // ... existing code for operands and redirection nodes ...
//         if (postfix->prio <= 1)
//         {
//             tree = new_node(postfix->value, postfix->prio, postfix->type, tool);
//             lst_add_back(&stack, lst_new(tree, tool));
//         }
//         else {  // Handling operators
//             tree = new_node(postfix->value, postfix->prio, postfix->type, tool);
//             if (tree->type == AND || tree->type == OR) {  // Special handling for &&
//                 if (!subtree_stack) {  // No previous subtree, start a new one
//                     lst_add_back(&subtree_stack, lst_new(tree, tool));
//                 } else {
//                     t_tree *right_subtree = pop_last(&subtree_stack);  // Get right subtree
//                     tree->right = right_subtree;  // Set right child of current &&
//                     lst_add_back(&subtree_stack, lst_new(tree, tool));  // Push current && with right child
//                 }
//             } else {
//                 t_tree *top_subtree = lst_peek(subtree_stack);  // Get top subtree (if any)
//                 if (top_subtree) {
//                     if (!is_redarection(tree->type)) {  // Only attach left for non-redirection operators
//                         top_subtree->left = tree;
//                 } 
//                 }
//             }
//             lst_add_back(&stack, lst_new(tree, tool));  // Can still add to main stack for some cases
//         }
//         postfix = postfix->next;
//     }

//     // Process subtree stack at the end
//     if (subtree_stack) {
//         if (lst_get_size(subtree_stack) == 1) {
//             tree = pop_last(&subtree_stack);
//         } else {
//            printf("Error: Invalid expression\n");
//         }
//     } else {
//         tree = pop_last(&stack);  // No && nodes, use the top element from the main stack
//     }

//     // ... rest of the code ...
//     update_tree(&tree, tool);
//     return (tree);
// }
