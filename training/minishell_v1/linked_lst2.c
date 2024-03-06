/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lst2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:27:36 by ymomen            #+#    #+#             */
/*   Updated: 2024/03/07 00:32:50 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"

void	ft_lstadd_front(t_lst **lst, t_lst *new)
{
	new->next = *lst;
	*lst = new;
}

t_lst	*lastone(t_lst *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	is_operateur(t_lst **node)
{
	if (!ft_strcmp((*node)->value, "("))
	{
		(*node)->prio = open_par;
		(*node)->type = OPEN_PARENTH;
		(*node)->read = (L_TO_R);
	}
	else if (!ft_strcmp((*node)->value, ")"))
	{
		(*node)->prio = close_par;
		(*node)->type = CLOSE_PARENTH;
		(*node)->read = (R_TO_L);
	}
	else if (!ft_strcmp((*node)->value, "&&"))
	{
		(*node)->prio = (and);
		(*node)->type = AND;
		(*node)->read = (R_TO_L);
	}
	else if (!ft_strcmp((*node)->value, "||"))
	{
		(*node)->prio = (or);
		(*node)->type = OR;
		(*node)->read = (R_TO_L);
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
		(*node)->type = APPEND_REDIRECTION;
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

void	init_type(t_lst *prev, t_lst *node)
{
	if (prev && node)
	{
		if (prev->type == REDIRECTION)
			node->type = OUTFILE;
		else if (prev->type == INPUT)
			node->type = INFILE;
		else if (prev->type == APPEND_REDIRECTION)
			node->type = OUTFILE_APPAND;
		else if (prev->type == HERE_DOC)
			node->type = LIMITER;
		else
			 if (node->type == 0)
			 {
                node->type = OPERAND;
                node->prio = 0;
                node->read = R_TO_L; 
			 }
	}
}
