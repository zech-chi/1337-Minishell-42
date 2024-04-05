/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:36:52 by zech-chi          #+#    #+#             */
/*   Updated: 2024/04/04 04:20:11 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

static void	ft_expand_quote(t_expand *exp, char *cmd)
{
	if (exp->quote == 0)
	{
		if (exp->i == 0 || ft_isspace(cmd[exp->i - 1]))
			exp->noting_before_quote = 1;
		exp->quote = cmd[exp->i];
	}
	else if (exp->quote == cmd[exp->i])
	{
		if (exp->noting_before_quote && cmd[exp->i - 1] == exp->quote
			&& (!cmd[exp->i + 1] || ft_isspace(cmd[exp->i + 1])))
			ft_lstadd_back(&(exp->head), ft_lstnew(ft_strdup2("")));
		exp->quote = 0;
		exp->noting_before_quote = 0;
	}
	else
	{
		exp->buff_exp = ft_strjoin2(exp->buff_exp, ft_char_to_str(cmd[exp->i]));
		exp->found_another_char = 1;
	}
}

static void	ft_expand_others(t_expand *exp, char c)
{
	exp->buff_exp = ft_strjoin2(exp->buff_exp, ft_char_to_str(c));
	if (c != '*' || exp->quote != 0)
		exp->found_another_char = 1;
	else
		exp->found_star = 1;
}

char	**ft_expand(char *cmd, t_env *env, int exit_status)
{
	t_expand	exp;

	if (!cmd)
		return (NULL);
	ft_exp_init(&exp);
	while (cmd[++(exp.i)])
	{
		if (ft_isspace(cmd[exp.i]) && exp.quote == 0)
			ft_expand_cut(&exp);
		else if (cmd[exp.i] == '"' || cmd[exp.i] == '\'')
			ft_expand_quote(&exp, cmd);
		else if (cmd[exp.i] == '$' && exp.quote != '\'')
			ft_expand_dollar(&exp, env, cmd, exit_status);
		else
			ft_expand_others(&exp, cmd[exp.i]);
		if (!cmd[exp.i])
			break ;
	}
	if (exp.buff_exp)
		ft_expand_cut(&exp);
	return (ft_lst_to_2d_char(&(exp.head)));
}
