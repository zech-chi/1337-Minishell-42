/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_lst_perfix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 00:42:19 by ymomen            #+#    #+#             */
/*   Updated: 2024/03/26 02:30:23 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

void	redarection_join_arg(t_lst **node)
{
	t_lst	*cur;
	t_lst	*hlf;
	t_lst	*cmd;

	cmd = NULL;
	cur = *node;
	while (cur)
	{
		if (cur->type == 0 && cur->next && is_redarection(cur->next->type))
			cmd = cur;
		else if (cur->type < 0 && cmd && cmd->next && cur->next
			&& cur->next->type == 0)
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

void	init_lvs(t_lst **head)
{
	t_lst	*node;
	int		i;

	i = 0;
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

void	deal_with_prac_dep(t_lst **head, t_lst *prev)
{
	t_lst	*node;
	t_lst	*close_par_lvl;
	t_lst	*fst;

	node = *head;
	while (node && node->next)
	{
		if (node->next->type == CLOSE_PARENTH && (*head)->type == OPEN_PARENTH
			&& node->next->lvl == (*head)->lvl)
			break ;
		node = node->next;
	}
	node = node->next;
	close_par_lvl = node;
	if (node->next && is_redarection(node->next->type))
	{
		node = node->next;
		fst = node;
		while (node->next && (is_redarection(node->next->type)
				|| node->next->type < 0))
			node = node->next;
		close_par_lvl->next = node->next;
		node->next = *head;
		if (prev)
			prev->next = fst;
		else
			*head = fst;
	}
}

void	redarection_perfix_lst(t_lst **head)
{
	t_lst	*cmd;
	t_lst	*red;
	t_lst	*node;
	t_lst	*prev;

	init_lvs(head);
	prev = NULL;
	node = *head;
	while (node)
	{
		if (node->type == OPEN_PARENTH)
		{
			deal_with_prac_dep(&node, prev);
			if (!prev)
				*head = node;
		}
		else if (node->type == 0 && node->next && is_redarection(node->next->type))
		{
			cmd = node;
			red = cmd->next;
			node = red->next;
			if (prev)
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
