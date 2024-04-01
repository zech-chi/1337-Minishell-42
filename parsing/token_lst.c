/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 23:32:33 by ymomen            #+#    #+#             */
/*   Updated: 2024/04/01 14:32:00 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

void	is_quot_parc_open(t_tool *tool, char command, int check)
{
	if (check >= 1 && command == '\'' && tool->quot == 0)
		tool->quot = 1;
	else if (check >= 1 && command == '\'' && tool->quot == 1)
		tool->quot = 0;
	else if (check >= 1 && command == '"' && tool->quot == 0)
		tool->quot = 2;
	else if (check >= 1 && command == '"' && tool->quot == 2)
		tool->quot = 0;
	if (check == 2 && tool->quot == 0)
	{
		if (command == '(')
			tool->prac += 1;
		else if (command == ')' && (tool->prac > 0))
			tool->prac -= 1;
		else if (command == ')' && tool->prac == 0)
			tool->prac = 451454545;
	}
}

t_lst	*check_parss_erres( t_lst **node, t_tool *tool)
{
	t_lst	*tmp;

	tmp = *node;
	if (tmp && (tmp->type == AND || tmp->type == OR || tmp->type == PIPE))
	{
		tool->err = 258;
		write(2, "🍪: syntax error near unexpected token `", 43);
		ft_putstr_fd(tmp->value, 2);
		write(2, "'\n", 2);
		return (NULL);
	}
	while (tmp)
	{
		if ((tmp->prio > 0 && !tmp->next && tmp->type != CLOSE_PARENTH) || (tmp->next && (tmp->prio > 2 && tmp->prio < 6 && tmp->next->prio > 0 && tmp->next->prio < 6))
			|| (tmp->next && tmp->type > 0 && tmp->next->type > 0 && tmp->type != CLOSE_PARENTH && tmp->next->type != OPEN_PARENTH  && !is_redarection(tmp->type) && !is_redarection(tmp->next->type))
			|| (is_redarection(tmp->type) && !(tmp->next->type < 0)) || ((tmp->type <= 0 && tmp->next && tmp->next->type == OPEN_PARENTH) || (tmp->type == CLOSE_PARENTH && tmp->next && tmp->next->type == 0)))
		{
			tool->err = 258;
			write(2, "🍪: syntax error near unexpected token `", 43);
			ft_putstr_fd(tmp->value, 2);
			write(2, "'\n", 2);
			return (NULL);
		}
		if (tmp->type == 10 && tmp->next && heredoc(tool, &(tmp->next->value)))
		{
			
			return (NULL);
		}
		tmp = tmp->next;
	}
	if (tool->prac || tool->quot || tool->err == 1)
	{
		if (tool->prac)
			write(2, "🍪: syntax error near unexpected token `)'\n", 46);
		else if (tool->err == 1)
			write(2, "🍪: syntax error near unexpected token `&'\n", 46);
		else
			write(2, "🍪: syntax error quot\n", 20);
		lst_clear(*node);
		return (NULL);
	}
	update_lst(node);
	trime(*node);
	redarection_join_arg(node);
	// redarection_perfix_lst(node);
	return (*node);
}

int	its_delimter(char *cmd, int *i, t_lst **node, t_garbage **grbg)
{
	int	err;

	err = 0;
	if (((is_delimter(cmd[*i + 1]) < 5) && (is_delimter(cmd[*i]) < 5))
		&& cmd[*i] == cmd[*i + 1])
	{
		lst_add_back(node, lst_new(ft_monstrdup(&cmd[*i], 2, grbg), grbg));
		*i += 1;
	}
	else if (is_delimter(cmd[*i]) == SINGL_AND
		&& is_delimter(cmd[*i + 1]) != SINGL_AND)
		err = 1;
	else
		lst_add_back(node, lst_new(ft_monstrdup(&cmd[*i], 1, grbg), grbg));
	return (err);
}

void	tokens_contu(t_lst **node, char *command, int *i, t_tool *tool)
{
	int		end;
	t_lst	*prev;
	
	prev = lastone(*node);
	if (prev && command[*i] && (prev->type == 1 || prev->type == 2
			|| prev->type == 9 || prev->type == 10))
	{
		end = *i;
		while (command[end] && (tool->quot || (command[end] != ' '
					&& !is_delimter(command[end]))))
			is_quot_parc_open(tool, command[++end], 1);
	}
	else
	{
		end = *i;
		while (command[end] && (tool->quot || !is_delimter(command[end])))
			is_quot_parc_open(tool, command[++end], 1);
	}
	if (end != *i)
	{
		lst_add_back(node, lst_new(ft_monstrdup(&command[*i], end - *i, &tool->grbg), &tool->grbg));
		*i = end -1;
		init_type_2((lastone(*node)), prev);
	}
}

t_lst	*tokens_lst(char *cmd, t_tool *tool)
{
	t_lst	*node;
	int		i;

	i = 0;
	tool->prac = 0;
	tool->quot = 0;
	node = NULL;
	while (cmd && cmd[i])
	{
		while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
			i++;
		is_quot_parc_open(tool, cmd[i], 2);
		if (cmd[i] && (is_delimter(cmd[i]) > 0) && tool->quot == 0)
			tool->err = its_delimter(cmd, &i, &node, &tool->grbg);
		else
			tokens_contu(&node, cmd, &i, tool);
		i++;
	}
	return (check_parss_erres(&node, tool));
}
