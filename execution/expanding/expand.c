/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:36:52 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/27 22:26:43 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

int	ft_is_valid_char(char c)
{
	return (('a' <= c && c <= 'z')
			|| ('A' <= c && c <= 'Z')
			|| ('0' <= c && c <= '9')
			|| (c == '_'));
}

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
			ft_lstadd_back(&(exp->head), ft_lstnew(ft_strdup2(exp->buff_exp)));
		free(exp->buff_exp);
		exp->buff_exp = NULL;
		exp->found_star = 0;
		exp->found_another_char = 0;
		exp->noting_before_env_var = 1;
		exp->noting_before_quote = 0;
	}
}

static void	ft_expand_help2(t_expand *exp, char *cmd)
{
	if (exp->quote == 0)
	{
		if (exp->i == 0 || ft_isspace(cmd[exp->i - 1]))
			exp->noting_before_quote = 1;
		exp->quote = cmd[exp->i];
	}
	else if (exp->quote == cmd[exp->i])
	{
		if (exp->noting_before_quote && cmd[exp->i - 1] == exp->quote && (!cmd[exp->i + 1] || ft_isspace(cmd[exp->i + 1])))
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
	int		i;

	if (exp->buff_exp)
		exp->noting_before_env_var = 0;
	exp->buff_env = ft_char_to_str(cmd[(exp->i)++]);
	while (cmd[exp->i] && ft_is_valid_char(cmd[exp->i]))
	{
		if (ft_is_numeric(cmd[exp->i]) && cmd[exp->i - 1] == '$')
		{
			free(exp->buff_env);
			exp->buff_env = NULL; // free
			break;
		}
		exp->buff_env = ft_strjoin2(exp->buff_env, ft_char_to_str(cmd[(exp->i)++]));
	}
	if (!exp->buff_env)
		return ;
	env_var = ft_env_search(env, exp->buff_env + 1);
	if (!env_var && exp->quote)
		exp->buff_exp = ft_strjoin2(exp->buff_exp, ft_strdup2(""));
	else
	{
		i = 0;
		while (env_var[i])
		{
			if (ft_isspace(env_var[i]))
				ft_expand_help1(exp);
			else
				exp->buff_exp = ft_strjoin2(exp->buff_exp, ft_char_to_str(env_var[i]));
			i++;
		}
	}
	if (exp->buff_exp)
		exp->found_another_char = 1;

	if (cmd[exp->i] == '*' && cmd[exp->i - 1] == '$')
		(exp->i)++;
	// I add this
	else if (cmd[exp->i] == '*')
		exp->found_star = 1;
	else if (ft_strlen2(exp->buff_env) == 1)
	{
		if (cmd[exp->i] == '?')
		{
			exp->buff_exp = ft_strjoin2(exp->buff_exp, ft_itoa2(exit_status));
			(exp->i)++;
		}
		else if ((cmd[exp->i] != '\'' && cmd[exp->i] != '"' && exp->quote == 0) || exp->quote != 0)
		{
			exp->buff_exp = ft_strjoin2(exp->buff_exp, ft_char_to_str('$'));
			exp->found_another_char = 1;
		}
	}
	(exp->i)--;
	(void)exit_status;
	free(exp->buff_env);
	free(env_var);
	exp->buff_env = NULL;
}
//void	ft_expand_help3(t_expand *exp, t_env *env, char *cmd, int exit_status)
//{
//	char	*env_var;

//	if (exp->buff_exp)
//		exp->noting_before_env_var = 0;
//	exp->buff_env = ft_char_to_str(cmd[(exp->i)++]);
//	while (cmd[exp->i] && ft_is_valid_char(cmd[exp->i]))
//	{
//		if (ft_is_numeric(cmd[exp->i]) && cmd[exp->i - 1] == '$')
//		{
//			free(exp->buff_env);
//			exp->buff_env = NULL; // free
//			break;
//		}
//		exp->buff_env = ft_strjoin2(exp->buff_env, ft_char_to_str(cmd[(exp->i)++]));
//	}
//	if (!exp->buff_env)
//		return ;
//	env_var = ft_env_search(env, exp->buff_env + 1);
//	if (!env_var && exp->quote)
//		exp->buff_exp = ft_strjoin2(exp->buff_exp, ft_strdup2(""));
//	else
//		exp->buff_exp = ft_strjoin2(exp->buff_exp, ft_strdup2(env_var));
		
//	if (exp->buff_exp)
//		exp->found_another_char = 1;

//	if (cmd[exp->i] == '*' && cmd[exp->i - 1] == '$')
//		(exp->i)++;
//	// I add this
//	else if (cmd[exp->i] == '*')
//		exp->found_star = 1;
//	else if (ft_strlen2(exp->buff_env) == 1)
//	{
//		if (cmd[exp->i] == '?')
//		{
//			exp->buff_exp = ft_strjoin2(exp->buff_exp, ft_itoa2(exit_status));
//			(exp->i)++;
//		}
//		else if ((cmd[exp->i] != '\'' && cmd[exp->i] != '"' && exp->quote == 0) || exp->quote != 0)
//		{
//			exp->buff_exp = ft_strjoin2(exp->buff_exp, ft_char_to_str('$'));
//			exp->found_another_char = 1;
//		}
//	}
//	(exp->i)--;
//	(void)exit_status;
//	free(exp->buff_env);
//	free(env_var);
//	exp->buff_env = NULL;
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

	if (!cmd)
		return (NULL);
	ft_exp_init(&exp);
	while (cmd[++(exp.i)])
	{
		if (ft_isspace(cmd[exp.i]) && exp.quote == 0)
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
	return (ft_lst_to_2d_char(&(exp.head)));
}
