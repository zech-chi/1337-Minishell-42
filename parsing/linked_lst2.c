/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lst2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:27:36 by ymomen            #+#    #+#             */
/*   Updated: 2024/04/03 15:59:03 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

t_lst	*lastone(t_lst *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	init_node(t_lst **node, int prio, int type, int read)
{
	(*node)->prio = prio;
	(*node)->type = type;
	(*node)->read = read;
}

void	init_type_2(t_lst *node, t_lst *prev)
{
	if (prev && node)
	{
		if (prev->type == REDIRECTION)
			init_node(&node, 0, OUTFILE, L_TO_R);
		else if (prev->type == INPUT)
			init_node(&node, 0, INFILE, L_TO_R);
		else if (prev->type == APPEND_REDIRECTION)
			init_node(&node, 0, OUTFILE_APPAND, L_TO_R);
		else if (prev->type == HERE_DOC)
			init_node(&node, 0, LIMITER, L_TO_R);
		else
			init_node(&node, 0, OPERAND, L_TO_R);
	}
}

void	init_type(t_lst **node)
{
	if (!ft_strcmp((*node)->value, "("))
		init_node(node, open_par, OPEN_PARENTH, L_TO_R);
	else if (!ft_strcmp((*node)->value, ")"))
		init_node(node, close_par, CLOSE_PARENTH, R_TO_L);
	else if (!ft_strcmp((*node)->value, "&&"))
		init_node(node, and, AND, R_TO_L);
	else if (!ft_strcmp((*node)->value, "||"))
		init_node(node, or, OR, R_TO_L);
	else if (!ft_strcmp((*node)->value, "|"))
		init_node(node, pip, PIPE, L_TO_R);
	else if (!ft_strcmp((*node)->value, ">"))
		init_node(node, redir, REDIRECTION, L_TO_R);
	else if (!ft_strcmp((*node)->value, ">>"))
		init_node(node, appand, APPEND_REDIRECTION, L_TO_R);
	else if (!ft_strcmp((*node)->value, "<<"))
		init_node(node, here_doc, HERE_DOC, L_TO_R);
	else if (!ft_strcmp((*node)->value, "<"))
		init_node(node, input, INPUT, L_TO_R);
	else
		init_node(node, -1, 0, L_TO_R);
}
