/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 06:15:50 by zech-chi          #+#    #+#             */
/*   Updated: 2024/04/16 16:42:59 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_execution.h"

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

static void	ft_help_expand_dollar(char *str, t_expand_herdoc *exp_h)
{
	if (str[exp_h->i] == '*' && str[exp_h->i - 1] == '$')
		(exp_h->i)++;
	if (ft_strlen2(exp_h->buff_env) == 1)
	{
		if (str[exp_h->i] == '?')
		{
			exp_h->buff_exp = ft_strjoin2(exp_h->buff_exp, \
			ft_itoa2(exp_h->exit_status));
			(exp_h->i)++;
		}
		else if (str[exp_h->i] == '$')
		{
			exp_h->buff_exp = ft_strjoin2(exp_h->buff_exp, ft_strdup2("$$"));
			(exp_h->i)++;
		}
		else
		{
			exp_h->buff_exp = ft_strjoin2(exp_h->buff_exp, ft_strdup2("$"));
		}
	}
	(exp_h->i)--;
}

static void	ft_herdoc_expand_dollar(char *str, t_expand_herdoc *exp_h)
{
	char	*env_var;

	env_var = NULL;
	exp_h->buff_env = ft_char_to_str(str[(exp_h->i)++]);
	while (str[exp_h->i] && ft_is_valid_char(str[exp_h->i]))
	{
		if (ft_is_numeric(str[exp_h->i]) && str[exp_h->i - 1] == '$')
		{
			free(exp_h->buff_env);
			exp_h->buff_env = NULL;
			break ;
		}
		exp_h->buff_env = ft_strjoin2(exp_h->buff_env, \
		ft_char_to_str(str[(exp_h->i)++]));
	}
	if (!(exp_h->buff_env))
		return ;
	env_var = ft_env_search(exp_h->env, exp_h->buff_env + 1);
	if (!env_var)
		exp_h->buff_exp = ft_strjoin2(exp_h->buff_exp, ft_strdup2(""));
	else
		exp_h->buff_exp = ft_strjoin2(exp_h->buff_exp, env_var);
	ft_help_expand_dollar(str, exp_h);
	free(exp_h->buff_env);
}

char	*ft_herdoc_expand(char *str, t_env *env, int exit_status)
{
	t_expand_herdoc	exp_h;

	exp_h.buff_env = NULL;
	exp_h.buff_exp = NULL;
	exp_h.i = 0;
	exp_h.exit_status = exit_status;
	exp_h.env = env;
	while (str[exp_h.i])
	{
		if (str[exp_h.i] == '$')
			ft_herdoc_expand_dollar(str, &exp_h);
		else
			exp_h.buff_exp = ft_strjoin2(exp_h.buff_exp, \
			ft_char_to_str(str[exp_h.i]));
		(exp_h.i)++;
	}
	return (exp_h.buff_exp);
}
