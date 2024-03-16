/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:36:52 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/16 21:29:38 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

static void	ft_expand_help1(t_expand *exp, t_env *env)
{
	if (exp->buff_exp)
	{
		if (exp->is_wild_card)
			ft_list_cwd(&(exp->head), env);
		else
			ft_lstadd_back(&(exp->head), ft_lstnew(exp->buff_exp));
		exp->buff_exp = NULL;
		exp->is_wild_card = 1;
	}
}

static void	ft_expand_help2(t_expand *exp, char c)
{
	if (exp->open == 0)
		exp->open = c;
	else if (exp->open == c)
		exp->open = 0;
	else
	{
		exp->buff_exp = ft_strjoin2(exp->buff_exp, ft_char_to_str(c));
		exp->is_wild_card = 0;
	}
}

static void	ft_expand_help3(t_expand *exp, t_env *env, char *cmd,
	int exit_status)
{
	exp->is_wild_card = 0;
	while (cmd[exp->i] && cmd[exp->i] == '$')
	{
		exp->buff_env = ft_char_to_str(cmd[(exp->i)++]);
		while (cmd[exp->i] && !ft_is_char_in_str(cmd[exp->i],
				"$,. +=?#@*[]\"'"))
			exp->buff_env = ft_strjoin2(exp->buff_env,
					ft_char_to_str(cmd[(exp->i)++]));
		exp->buff_exp = ft_strjoin2(exp->buff_exp,
				ft_env_search(env, exp->buff_env + 1));
		if (cmd[exp->i] == '?' && ft_strlen2(exp->buff_env) == 1)
			exp->buff_exp = ft_strjoin2(exp->buff_exp, ft_itoa2(exit_status));
		else if (cmd[exp->i] == ' ')
			ft_expand_help1(exp, env);
		else if (cmd[exp->i] == '"' || cmd[exp->i] == '\'')
			ft_expand_help2(exp, cmd[exp->i]);
		else if (cmd[exp->i] && cmd[exp->i] != '$' && cmd[exp->i] != ' ')
			exp->buff_exp = ft_strjoin2(exp->buff_exp,
					ft_char_to_str(cmd[exp->i]));
		else if (ft_strlen2(exp->buff_env) == 1 && !cmd[exp->i])
			exp->buff_exp = ft_strjoin2(exp->buff_exp, exp->buff_env);
		exp->buff_env = NULL;
	}
}

static void	ft_expand_help4(t_expand *exp, char c)
{
	exp->buff_exp = ft_strjoin2(exp->buff_exp, ft_char_to_str(c));
	if (c != '*' || exp->open != 0)
		exp->is_wild_card = 0;
}

char	**ft_expand(char *cmd, t_env *env, int exit_status)
{
	t_expand	exp;

	ft_exp_init(&exp);
	while (cmd[++(exp.i)])
	{
		if (cmd[exp.i] == ' ' && exp.open == 0)
			ft_expand_help1(&exp, env);
		else if (cmd[exp.i] == '"' || cmd[exp.i] == '\'')
			ft_expand_help2(&exp, cmd[exp.i]);
		else if (cmd[exp.i] == '$' && exp.open != '\'')
			ft_expand_help3(&exp, env, cmd, exit_status);
		else
			ft_expand_help4(&exp, cmd[exp.i]);
		if (!cmd[exp.i])
			break ;
	}
	if (exp.buff_exp)
		ft_expand_help1(&exp, env);
	return (ft_lst_to_2d_char(exp.head));
}
