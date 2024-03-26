/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_lst_perfix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 00:42:19 by ymomen            #+#    #+#             */
/*   Updated: 2024/03/25 23:49:13 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

void redarection_join_arg(t_lst **node)
{
	t_lst *cur;
	t_lst *cmd =NULL;
	t_lst *operater = NULL;
	t_lst *hlf;
	cur = *node;
	while (cur)
	{
		if (cur->type == 0 && cur->next && (cur->next->type == INPUT || cur->next->type == REDIRECTION || cur->next->type == APPEND_REDIRECTION || cur->next->type == HERE_DOC))
		{
			cmd = cur;
			operater = cmd->next;
		}
		else if (cur->type < 0 && cmd && operater && cur->next && cur->next->type == 0)
		{
				hlf = cur->next;
				cmd ->value = ft_strjoin(cmd->value, ft_strdup(" "));
				cmd->value = ft_strjoin(cmd->value, hlf->value);
				cur->next = hlf->next;
				free(hlf);
				cmd = NULL;
		}
		cur = cur->next;
	}
}
void init_lvs(t_lst **head)
{
    t_lst *node;
    int i = 0;
    
    node = *head;
    while (node)
    {
        if (node->type == OPEN_PARENTH)
            i++;
        node->lvl = i;
        if (node->type == CLOSE_PARENTH)
            i--;
		node = node->next;
    }
 
}
int deal_with_prac_dep(t_lst **head, t_lst *prev)
{
	t_lst *node;
	t_lst *close_par_lvl;

	node = *head;
	while(node && node->next)
	{
		if (node->next->type == CLOSE_PARENTH &&  (*head)->type == OPEN_PARENTH && node->next->lvl == (*head)->lvl)
			break;
		node = node->next;
	}
	node = node->next;
	close_par_lvl = node;
	if (node->next && is_redarection(node->next->type))
	{
		node = node->next;
		t_lst *fst = node;
		while (node->next && (is_redarection(node->next->type) || node->next->type < 0))
			node = node->next;
		close_par_lvl->next = node->next;
		node->next = *head;
		if (prev)
			prev->next = fst;
		else
			*head = fst;
		return (1);
	}
	return (0);
}

void redarection_perfix_lst(t_lst **head)
{
	t_lst *cmd;
	t_lst *red;
	t_lst *node;
	t_lst *prev = NULL;

	init_lvs(head);
	node = *head;
	while (node)
	{
		if (node->type == OPEN_PARENTH) {
			deal_with_prac_dep(&node, prev);
			if (!prev)
				*head = node;
		}
		else if (node->type == 0 && node->next && is_redarection(node->next->type))
		{
			cmd = node;
			red = cmd->next;
			node = red->next;
			if(prev)
				prev->next = cmd->next;
			else
				*head = cmd->next;
			while (node && node->next && (node->next->type < 0 || is_redarection(node->next->type)))
				node = node->next;
			cmd->next = node->next;
			node->next = cmd;
		}
		prev = node;
		node = node->next;
	}
	node = *head;
}

