/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:16:49 by ymomen            #+#    #+#             */
/*   Updated: 2024/04/18 16:36:34 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

void	ft_clearhd(t_lst *here_doc)
{
	while (here_doc)
	{
		unlink(here_doc->value);
		here_doc = here_doc->next;
	}
}

static int	condtion(t_lst *n)
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
	int		lst;
	t_lst	*here_doc;

	lst = 0;
	here_doc = NULL;
	while (node)
	{
		if (node->type > 0 && !is_redarection(node->type))
			lst = node->type;
		if (condtion(node) || (lst && lst == CLOSE_PARENTH && node->type == 0))
		{
			tool->err = 258;
			write(2, "🍪: syntax error near unexpected token `", 43);
			ft_putstr_fd(node->value, 2);
			write(2, "'\n", 2);
			return (ft_clearhd(here_doc), 1);
		}
		if (node->type == 10 && node->next
			&& heredoc(tool, &(node->next->value), &here_doc))
			return (ft_clearhd(here_doc), \
			write(2, "error in here_doc \n", 20), 1);
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
	if (parssing_error_2(tmp, tool))
		return (1);
	if (tool->prac || tool->quot || tool->anderr == 1)
	{
		if (tool->prac)
			write(2, "🍪: syntax error near unexpected token `)'\n", 46);
		else if (tool->anderr == 1)
			write(2, "🍪: syntax error near unexpected token `&'\n", 46);
		else
			write(2, "🍪: syntax error quot\n", 25);
		tool->err = 258;
		return (1);
	}
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
