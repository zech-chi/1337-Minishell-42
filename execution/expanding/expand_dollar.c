/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:04:46 by zech-chi          #+#    #+#             */
/*   Updated: 2024/04/03 00:23:11 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

static int	ft_is_valid_char(char c)
{
	return (('a' <= c && c <= 'z')
		|| ('A' <= c && c <= 'Z')
		|| ('0' <= c && c <= '9')
		|| (c == '_'));
}

static int	ft_is_numeric(char c)
{
	return ('0' <= c && c <= '9');
}

/*
		else if ((cmd[exp->i] != '\'' && cmd[exp->i] != '"' && exp->quote == 0)
			|| exp->quote != 0)
		{
			exp->buff_exp = ft_strjoin2(exp->buff_exp, ft_char_to_str('$'));
			exp->found_another_char = 1;
			//(exp->i)++;
		}
*/
static void	ft_help(t_expand *exp, char *cmd, int exit_status, char *env_var)
{
	if (cmd[exp->i] == '*' && cmd[exp->i - 1] == '$')
		(exp->i)++;
	else if (cmd[exp->i] == '*')
		exp->found_star = 1;
	if (ft_strlen2(exp->buff_env) == 1)
	{
		if (cmd[exp->i] == '?')
		{
			exp->buff_exp = ft_strjoin2(exp->buff_exp, ft_itoa2(exit_status));
			(exp->i)++;
		}
		else if ((cmd[exp->i] != '\'' && cmd[exp->i] != '"' && exp->quote == 0)
			|| exp->quote != 0)
		{
			exp->buff_exp = ft_strjoin2(exp->buff_exp, ft_char_to_str('$'));
			exp->found_another_char = 1;
		}
	}
	(exp->i)--;
	free(exp->buff_env);
	free(env_var);
	exp->buff_env = NULL;
}

static void	ft_add_to_expand_buffer(t_expand *exp, char *env_var)
{
	int		i;

	i = 0;
	while (env_var[i])
	{
		if (ft_isspace(env_var[i]))
			ft_expand_cut(exp);
		else
			exp->buff_exp = ft_strjoin2(exp->buff_exp,
					ft_char_to_str(env_var[i]));
		i++;
	}
	exp->found_another_char = 1;
}

void	ft_expand_dollar(t_expand *exp, t_env *env, char *cmd, int exit_status)
{
	char	*env_var;

	exp->buff_env = ft_char_to_str(cmd[(exp->i)++]);
	while (cmd[exp->i] && ft_is_valid_char(cmd[exp->i]))
	{
		if (ft_is_numeric(cmd[exp->i]) && cmd[exp->i - 1] == '$')
		{
			free(exp->buff_env);
			exp->buff_env = NULL;
			break ;
		}
		exp->buff_env = ft_strjoin2(exp->buff_env,
				ft_char_to_str(cmd[(exp->i)++]));
	}
	if (!exp->buff_env)
		return ;
	env_var = ft_env_search(env, exp->buff_env + 1);
	if (!env_var && exp->quote)
		exp->buff_exp = ft_strjoin2(exp->buff_exp, ft_strdup2(""));
	else if (env_var)
		ft_add_to_expand_buffer(exp, env_var);
	ft_help(exp, cmd, exit_status, env_var);
}
