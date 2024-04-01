/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 23:32:33 by ymomen            #+#    #+#             */
/*   Updated: 2024/03/31 23:51:10 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

void	is_quot_parc_open(t_parse *par_line, char command, int check)
{
	if (check >= 1 && command == '\'' && par_line->quot == 0)
		par_line->quot = 1;
	else if (check >= 1 && command == '\'' && par_line->quot == 1)
		par_line->quot = 0;
	else if (check >= 1 && command == '"' && par_line->quot == 0)
		par_line->quot = 2;
	else if (check >= 1 && command == '"' && par_line->quot == 2)
		par_line->quot = 0;
	if (check == 2 && par_line->quot == 0)
	{
		if (command == '(')
			par_line->prac += 1;
		else if (command == ')' && (par_line->prac > 0))
			par_line->prac -= 1;
		else if (command == ')' && par_line->prac == 0)
			par_line->prac = 451454545;
	}
}

t_lst	*check_parss_erres(t_parse parc_line, t_lst **node, int *err)
{
	t_lst	*tmp;

	tmp = *node;
	if (tmp && (tmp->type == AND || tmp->type == OR || tmp->type == PIPE))
	{
		*err = 258;
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
			*err = 258;
			write(2, "🍪: syntax error near unexpected token `", 43);
			ft_putstr_fd(tmp->value, 2);
			write(2, "'\n", 2);
			return (NULL);
		}
		if (tmp->type == 10 && tmp->next && heredoc(err, &(tmp->next->value)))
		{
			
			return (NULL);
		}
		tmp = tmp->next;
	}
	if (parc_line.prac || parc_line.quot || parc_line.err == 1)
	{
		if (parc_line.prac)
			write(2, "🍪: syntax error near unexpected token `)'\n", 46);
		else if (parc_line.err == 1)
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

void	its_delimter(char *cmd, int *i, t_lst **node, t_parse *par_line)
{
	par_line->err = 0;
	if (((is_delimter(cmd[*i + 1]) < 5) && (is_delimter(cmd[*i]) < 5))
		&& cmd[*i] == cmd[*i + 1])
	{
		lst_add_back(node, lst_new(ft_monstrdup(&cmd[*i], 2)));
		*i += 1;
	}
	else if (is_delimter(cmd[*i]) == SINGL_AND
		&& is_delimter(cmd[*i + 1]) != SINGL_AND)
		par_line->err = 1;
	else
		lst_add_back(node, lst_new(ft_monstrdup(&cmd[*i], 1)));
}

void	tokens_contu(t_lst **node, char *command, int *i, t_parse *par_line)
{
	int		end;
	t_lst	*prev;

	prev = lastone(*node);
	if (prev && command[*i] && (prev->type == 1 || prev->type == 2
			|| prev->type == 9 || prev->type == 10))
	{
		end = *i;
		while (command[end] && (par_line->quot || (command[end] != ' '
					&& !is_delimter(command[end]))))
			is_quot_parc_open(par_line, command[++end], 1);
	}
	else
	{
		end = *i;
		while (command[end] && (par_line->quot || !is_delimter(command[end])))
			is_quot_parc_open(par_line, command[++end], 1);
	}
	if (end != *i)
	{
		lst_add_back(node, lst_new(ft_monstrdup(&command[*i], end - *i)));
		*i = end -1;
		init_type_2((lastone(*node)), prev);
	}
}

t_lst	*tokens_lst(char *cmd, int *err)
{
	t_lst	*node;
	t_parse	par_line;
	int		i;

	i = 0;
	par_line.prac = 0;
	par_line.quot = 0;
	node = NULL;
	while (cmd && cmd[i])
	{
		while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
			i++;
		is_quot_parc_open(&par_line, cmd[i], 2);
		if (cmd[i] && (is_delimter(cmd[i]) > 0) && par_line.quot == 0)
		{
			its_delimter(cmd, &i, &node, &par_line);
		}
		else
			tokens_contu(&node, cmd, &i, &par_line);
		i++;
	}
	return (check_parss_erres(par_line, &node, err));
}
