/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:36:52 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/21 00:48:13 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

int	ft_is_numeric(char c)
{
	return ('0' <= c && c <= '9');
}

static void	ft_expand_help1(t_expand *exp)
{
	if (exp->buff_exp)
	{
		if (exp->found_star && !exp->found_another_char)
			ft_list_cwd(&(exp->head));
		else
			ft_lstadd_back(&(exp->head), ft_lstnew(exp->buff_exp));
		exp->buff_exp = NULL;
		exp->found_star = 0;
		exp->found_another_char = 0;
	}
}

static void	ft_expand_help2(t_expand *exp, char *cmd)
{
	if (exp->quote == 0)
	{
		if (exp->i == 0 || cmd[exp->i - 1] == ' ')
			exp->noting_before_quote = 1;
		exp->quote = cmd[exp->i];
	}
	else if (exp->quote == cmd[exp->i])
	{
		if (exp->noting_before_quote && cmd[exp->i - 1] == exp->quote && (!cmd[exp->i + 1] || cmd[exp->i + 1] == ' '))
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

void	ft_expand_help3(t_expand *exp, t_env *env, char *cmd, int exit_status)
{
	char	*env_var;
	char	*buff_star;

	buff_star = NULL;
	exp->found_another_char = 1;
	while (cmd[exp->i] && cmd[exp->i] == '$')
	{
		exp->buff_env = ft_char_to_str(cmd[(exp->i)++]);
		while (cmd[exp->i] && !ft_is_delimiter(cmd[exp->i]))
		{
			if (ft_is_numeric(cmd[exp->i]) && cmd[exp->i - 1] == '$')
			{
				exp->buff_env = NULL;
				break;
			}
			else
				exp->buff_env = ft_strjoin2(exp->buff_env, ft_char_to_str(cmd[(exp->i)++]));
		}
		if (!exp->buff_env)
			break;
		env_var = ft_env_search(env, exp->buff_env + 1);
		exp->buff_exp = ft_strjoin2(exp->buff_exp, env_var);
		if (!env_var && !exp->buff_exp && !exp->buff_env)
			exp->found_another_char = 0;
		if (cmd[exp->i] == '*')
		{
			while (cmd[exp->i] == '*')
			{
				buff_star = ft_strjoin2(buff_star, ft_char_to_str(cmd[exp->i++]));
				(exp->i)++;
			}
			//exp->found_star = 1;
			if (!(exp->found_another_char) && (!cmd[exp->i] || cmd[exp->i] == ' '))
				ft_list_cwd(&(exp->head));
			
		}
		else if (cmd[exp->i] == '?' && ft_strlen2(exp->buff_env) == 1)
			exp->buff_exp = ft_strjoin2(exp->buff_exp, ft_itoa2(exit_status));
		else if (cmd[exp->i] == ' ' && exp->quote == 0)
			ft_expand_help1(exp);
		else if (cmd[exp->i] == '"' || cmd[exp->i] == '\'')
			ft_expand_help2(exp, cmd);
		else if (cmd[exp->i] && cmd[exp->i] != '$' && cmd[exp->i] != ' ')
			exp->buff_exp = ft_strjoin2(exp->buff_exp,
					ft_char_to_str(cmd[exp->i]));
		else if (ft_strlen2(exp->buff_env) == 1 && !cmd[exp->i])
			exp->buff_exp = ft_strjoin2(exp->buff_exp, exp->buff_env);
		exp->buff_env = NULL;
	}
}


//static void	ft_expand_help3_1(t_expand *exp, t_env *env, char *cmd, int exit_status)
//{
//	exp->buff_env = ft_char_to_str(cmd[(exp->i)++]);
//	while ()
//}

static void	ft_expand_help4(t_expand *exp, char c)
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

	ft_exp_init(&exp);
	while (cmd[++(exp.i)])
	{
		if (cmd[exp.i] == ' ' && exp.quote == 0)
			ft_expand_help1(&exp);
		else if (cmd[exp.i] == '"' || cmd[exp.i] == '\'')
			ft_expand_help2(&exp, cmd);
		else if (cmd[exp.i] == '$' && exp.quote != '\'')
			ft_expand_help3(&exp, env, cmd, exit_status);
		else
			ft_expand_help4(&exp, cmd[exp.i]);
		if (!cmd[exp.i])
			break ;
	}
	if (exp.buff_exp)
		ft_expand_help1(&exp);
	(void)(exit_status);
	(void)(env);
	return (ft_lst_to_2d_char(exp.head));
}
