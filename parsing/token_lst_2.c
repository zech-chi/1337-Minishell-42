/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:16:49 by ymomen            #+#    #+#             */
/*   Updated: 2024/04/03 14:56:41 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

static int	intcondtion(t_lst *n)
{
	if (n->prio > 0 && !n->next && n->type != CLOSE_PARENTH)
		return (1);
	if (n->next && (n->prio > 2 && n->prio < 6 && n->next->prio > 2
			&& n->next->prio < 6))
		return (1);
	if (n->next && n->type > 0 && n->next->type > 0 && n->type != CLOSE_PARENTH
		&& n->next->type != OPEN_PARENTH && !is_redarection(n->type)
		&& !is_redarection(n->next->type))
		return (1);
	if ((is_redarection(n->type) && !(n->next->type < 0)) || ((n->type <= 0
				&& n->next && n->next->type == OPEN_PARENTH)
			|| (n->type == CLOSE_PARENTH && n->next && n->next->type == 0))
		|| (n->next && n->type == n->next->type && n->next->type <= 0))
		return (1);
	return (0);
}

static int	parssing_error_2(t_lst *node, t_tool *tool)
{
	while (node)
	{
		if (intcondtion(node))
		{
			tool->err = 258;
			write(2, "🍪: syntax error near unexpected token `", 43);
			ft_putstr_fd(node->value, 2);
			write(2, "'\n", 2);
			return (1);
		}
		if (node->type == 10 && node->next
			&& heredoc(tool, &(node->next->value)))
			return (write(2, "error in here_doc \n", 20), 1);
		node = node->next;
	}
	return (0);
}

int	parssing_error(t_lst **node, t_tool *tool)
{
	t_lst	*tmp;

	tmp = *node;
	if (tmp && (tmp->type == AND || tmp->type == OR || tmp->type == PIPE))
	{
		tool->err = 258;
		write(2, "🍪: syntax error near unexpected token `", 43);
		ft_putstr_fd(tmp->value, 2);
		write(2, "'\n", 2);
		return (1);
	}
	if (tool->prac || tool->quot || tool->anderr == 1)
	{
		if (tool->prac)
			write(2, "🍪: syntax error near unexpected token `)'\n", 46);
		else if (tool->anderr == 1)
			write(2, "🍪: syntax error near unexpected token `&'\n", 46);
		else
			write(2, "🍪: syntax error quot\n", 20);
		tool->err = 258;
		return (1);
	}
	if (parssing_error_2(tmp, tool))
		return (1);
	return (0);
}

void	update_lst(t_lst **head, t_tool *tool)
{
	t_lst	*node;
	char	*str;

	node = *head;
	while (node && node->next)
	{
		if (is_redarection(node->type) && node->next->type < -1)
		{
			str = ft_strjoin(node->value, ft_strdup(" ", tool), tool);
			str = ft_strjoin(str, node->next->value, tool);
			node->value = str;
			node->next = node->next->next;
		}
		node = node->next;
	}
}
