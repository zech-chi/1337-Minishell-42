/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infix_to_Postfix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:27:36 by ymomen            #+#    #+#             */
/*   Updated: 2024/02/29 23:32:25 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"
#include <ctype.h> 

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s2[i] - s1[i]);
		i++;
	}
	return (0);
}
void is_operateur(t_lst **node)
{
	if (!ft_strcmp((*node)->value, "("))
	{
		(*node)->prio = open_par;
		(*node)->type = OPEN_PARENTH;
		(*node)->read = (L_TO_R);
	}
	else if (!ft_strcmp((*node)->value, ")"))
	{
		(*node)->prio =  (close_par);
		(*node)->type = CLOSE_PARENTH;
		(*node)->read = (R_TO_L);
	}
	else if (!ft_strcmp((*node)->value, "&&"))
	{
		(*node)->prio = (and);
		(*node)->type = AND;
		(*node)->read = (L_TO_R);
	}
	else if (!ft_strcmp((*node)->value, "||"))
	{
		(*node)->prio = (or);
		(*node)->type = OR;
		(*node)->read = (L_TO_R);
	}
	else if (!ft_strcmp((*node)->value, "|"))
	{
		(*node)->prio = (pip);
		(*node)->type = PIPE;
		(*node)->read = (L_TO_R);
	}
	else if (!ft_strcmp((*node)->value, ">"))
	{
		(*node)->prio = (redir);
		(*node)->type = REDIRECTION;
		(*node)->read = (L_R_R_L);
	}
	else if (!ft_strcmp((*node)->value, ">>"))
	{
		(*node)->prio = (appand);
		(*node)->type = APEND_REDIRECTION;
		(*node)->read = (L_R_R_L);
	}
	else if (!ft_strcmp((*node)->value, "<<"))
	{
		(*node)->prio = (here_doc);
		(*node)->type = HERE_DOC;
		(*node)->read = (L_R_R_L);
	}
	else if (!ft_strcmp((*node)->value, "<"))
	{
		(*node)->prio = (input);
		(*node)->type = INPUT;
		(*node)->read = (L_R_R_L);
	}
	else
	{
		(*node)->prio = -1;
		(*node)->type = 0;
		(*node)->read = -1;
	}
}
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
