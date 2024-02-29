/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:51:50 by ymomen            #+#    #+#             */
/*   Updated: 2024/02/29 22:54:26 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"

char	*ft_strchr_v2(const char *s, int c, char *del)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (*del = c ,(char *) s + i);
		i++;
	}
	if (s[i] == (char)c)
		return (*del = c ,(char *)s + i);
	return (NULL);
}

// char **lst_to_arr(t_lst *head)
// {
// 	int size = size_lst(&head);
// 	char **arr;
// 	int i = 0;
// 	t_lst *node;

// 	node = head;
// 	arr= (char **) malloc(sizeof (char *) * (size + 1));
// 	if (!arr)
// 		return (NULL);
// 	while (node && i < size)
// 	{
// 		arr[i] = ft_strtrim(node->value, " ");
// 		 if (check_arr(arr[i]))
// 			i++;
// 		else
// 			free(arr[i]);	
// 		node = node->next;
// 	}
// 	arr[i] = NULL;
// 	lst_clear(head);
// 	return (arr);
// }


// void *pop_last(t_lst **stack) {
//     if (!stack || !*stack) {
//         return (stack = NULL);
//     }

//     t_lst *prev = NULL;
//     t_lst *current = *stack;

//     while (current->next) {
//         prev = current;
//         current = current->next;
//     }

//     void *value = current->value; // Assuming value is a member of t_lst
//     free(current);

//     if (prev) {
//         prev->next = NULL;
//     } else {
//         *stack = NULL;
//     }

//     return value;
// }

void	ft_lstadd_front(t_lst **lst, t_lst *new)
{
	new->next = *lst;
	*lst = new;
}



// t_tree *postfix_tree(t_lst *postfix) {
//     t_stack *stack = NULL;
//     while (postfix != NULL) {
//         if (postfix->prio == -1) {
//             // Create a leaf node for the operand
//             t_tree *node = new_node(postfix->value);
//             stack_add_back(&stack, stack_new(node));
//         } else {
//             // Create a new operator node
//             t_tree *operator_node = new_node(postfix->value);
//             // Ensure the stack has at least two elements before popping
//             if (size_stack(&stack) < 2) {
//                 // Handle invalid expression with insufficient operands (optional)
//                 printf("Error: Invalid postfix expression (missing operands).\n");
//                 return NULL; // Or handle the error differently
//             }
//             // Pop two elements from the stack (right and left subtrees)
//             t_tree *right_node = pop_stack(&stack);
//             t_tree *left_node = pop_stack(&stack);
//             // Assign subtrees to the operator node
//             operator_node->right = right_node;
//             operator_node->left = left_node;
//             // Push the operator node back onto the stack
//             stack_add_back(&stack, stack_new(operator_node));
//         }
//         postfix = postfix->next;
//     }
//     // Return the final tree (the only element remaining on the stack)
//     return (t_tree *)pop_stack(&stack);
// }





// t_tree	*tree_new(int value);
// char	*ft_strchr_v2(const char *s, int c, char *del);
// char	*ft_strtok(char *str);
// t_tree	*creat_tree(char *str);
// void	ft_bzero(void *s, size_t n);