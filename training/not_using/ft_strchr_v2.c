/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:51:50 by ymomen            #+#    #+#             */
/*   Updated: 2024/03/07 00:34:36 by ymomen           ###   ########.fr       */
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



void hpl(t_lst **postfix, t_lst *head, t_lst *stack)
{

	t_lst *prev = NULL;
	t_lst *pop = NULL;
	prev = lastone(stack);
	if (prev && prev->prio == head->prio)
	{
		while (prev && ( head->read != prev->read))
		{
			pop = lst_new((void *) pop_last(&stack));
			if (pop->type != OPEN_PARENTH && pop->type != CLOSE_PARENTH)
				lst_add_back(postfix, pop);
			prev = lastone(stack);
		}
		lst_add_back(&stack, lst_new(head->value));
	}
	else if (prev && prev->prio > head->prio)
	{
		while(prev && prev->prio > head->prio)
		{
			pop = lst_new((void *) pop_last(&stack));
			if (pop->type != OPEN_PARENTH && pop->type != CLOSE_PARENTH)
				lst_add_back(postfix, pop);
			prev = lastone(stack);
		}
		lst_add_back(&stack, lst_new(head->value));
	}
	else if ( prev && prev->prio < head->prio)
		lst_add_back(&stack, lst_new(head->value));
}
void from_infix_to_Postfix(t_lst *head, t_lst **postfix)
{												
	t_lst *stack = NULL;
	int parc = 0;
	t_lst *pop = NULL;
	
	while(head)
	{
		is_parc_open(&parc, head->value[0], 0);
		if(head->prio == -1)
			lst_add_back(postfix, lst_new(head->value));
		else if (!stack || parc)
				lst_add_back(&stack, lst_new(head->value));
		else if (head->type == CLOSE_PARENTH)
		{
			while(lastone(stack)->type != OPEN_PARENTH)
			{
				pop = lst_new((void *) pop_last(&stack));
				if (pop->type != OPEN_PARENTH && pop->type != CLOSE_PARENTH)
					lst_add_back(postfix, pop);
			}
			pop = lst_new((void *) pop_last(&stack));
		}
		else
			hpl(postfix,head, stack);
		head = head->next;
	}
	while(size_lst(&stack) > 0)	
		{
			pop = lst_new((void *) pop_last(&stack));
			if (pop->type != OPEN_PARENTH && pop->type != CLOSE_PARENTH)
				lst_add_back(postfix, pop);
		}
}

t_tree *postfix_tree(t_lst *postfix)
{
	t_stack *stack = NULL;
	t_tree *tree = NULL;
	while(postfix)
	{
		if (postfix->prio == -1)
		{
			tree = new_node(postfix->value);
			stack_add_back(&stack, stack_new(tree));
		}
		else
		{
			tree = new_node(postfix->value);
			tree->right = (t_tree *)(pop_stack(&stack));
			tree->left= (t_tree *)(pop_stack(&stack));
			stack_add_back(&stack, stack_new(tree));
		}
		postfix = postfix->next;
	}
	tree = pop_stack(&stack);
	return (tree);
}

	/*stack*/
t_stack *lastonstack(t_stack *head);
void	ft_stackadd_front(t_stack **stack, t_stack *new);
void *pop_stack(t_stack **stack);
void stack_clear(t_stack *head);
int size_stack(t_stack **head);
void stack_add_back(t_stack **head, t_stack *node);
t_stack *stack_new(void *str);









// void hpl(t_lst **postfix, t_lst *head, t_lst *stack)
// {

// 	t_lst *prev = NULL;
// 	t_lst *pop = NULL;
// 	prev = lastone(stack);
// 			// if (prev && prev->prio == head->prio)
// 			// {
// 			// 	while (prev && (head->prio == prev->prio))
// 			// 	{
// 			// 		pop = lst_new((void *) pop_last(&stack));
// 			// 		if (pop->type != OPEN_PARENTH && pop->type != CLOSE_PARENTH)
// 			// 			lst_add_back(postfix, pop);
// 			// 		prev = lastone(stack);
// 			// 	}
// 			// 		lst_add_back(&stack, lst_new(head->value));
// 			// }
// 			if (head->type > 0)
// 			{
// 				while (stack && prev->type != OPEN_PARENTH &&
//                        (prev->prio >= head->prio ||
//                         (prev->prio == head->prio && prev->read == R_TO_L)))
// 				{
// 					pop = lst_new((void *) pop_last(&stack));
// 					if (pop->type != OPEN_PARENTH && pop->type != CLOSE_PARENTH)
// 						lst_add_back(postfix, pop);
// 					prev = lastone(stack);
// 				}
// 				lst_add_back(&stack, lst_new(head->value));
// 			}
// }
// t_lst *from_infix_to_Postfix(t_lst *head)
// {												
// 	t_lst *stack = NULL;
// 	t_lst *postfix = NULL;
// 	 t_parse prac;
// 	prac.prac = 0;
// 	prac.prac = 0;
// 	t_lst *pop = NULL;
	
// 	while(head)
// 	{
// 		is_quot_parc_open(&prac, head->value[0]);
// 		if(head->type == 0)
// 			lst_add_back(&postfix, lst_new(head->value));
// 		else if (!stack || prac.prac)
// 				lst_add_back(&stack, lst_new(head->value));
// 		else if (head->type == CLOSE_PARENTH)
// 		{
// 			while(lastone(stack)->type != OPEN_PARENTH)
// 			{
// 				pop = lst_new((void *) pop_last(&stack));
// 				if (pop->type != OPEN_PARENTH && pop->type != CLOSE_PARENTH)
// 					lst_add_back(&postfix, pop);
// 			}
// 			pop_last(&stack);
// 		}
// 		else
// 			hpl(&postfix,head, stack);
// 		head = head->next;
// 	}
// 	while(stack)	
// 		{
// 			pop = lst_new((void *) pop_last(&stack));
// 			if (pop->type != OPEN_PARENTH && pop->type != CLOSE_PARENTH)
// 				lst_add_back(&postfix, pop);
// 		}
// 		return (postfix);
// }