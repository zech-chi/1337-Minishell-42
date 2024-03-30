/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 06:15:50 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/30 03:02:57 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_execution.h"

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

void	ft_help_expand_dollar(char *str, int *i, char **buff_env, char **buff_exp, int exit_status)
{
	if (str[*i] == '*' && str[*i - 1] == '$')
		(*i)++;
	if (ft_strlen2(*buff_env) == 1)
	{
		if (str[*i] == '?')
		{
			*buff_exp = ft_strjoin2(*buff_exp, ft_itoa2(exit_status));
			(*i)++;
		}
		else
		{
			*buff_exp = ft_strjoin2(*buff_exp, ft_char_to_str('$'));
		}
	}
	(*i)--;
}

void	ft_herdoc_expand_dollar(char *str, char **buff_exp, int *i, t_env *env, int exit_status)
{
	char	*buff_env;
	char	*env_var;

	buff_env = NULL;
	env_var = NULL;
	buff_env = ft_char_to_str(str[(*i)++]);
	while (str[*i] && ft_is_valid_char(str[*i]))
	{
		if (ft_is_numeric(str[*i]) && str[*i - 1] == '$')
		{
			free(buff_env);
			buff_env = NULL;
			break;
		}
		buff_env = ft_strjoin2(buff_env, ft_char_to_str(str[(*i)++]));
	}
	if (!buff_env)
		return ;
	env_var = ft_env_search(env, buff_env + 1);
	if (!env_var)
		*buff_exp = ft_strjoin2(*buff_exp, ft_strdup2(""));
	else
		*buff_exp = ft_strjoin2(*buff_exp, env_var);
	ft_help_expand_dollar(str, i, &buff_env, buff_exp, exit_status);
	//free(buff_env);
	//free(env_var);
}

char	*ft_herdoc_expand(char *str, t_env *env, int exit_status)
{
	char	*buff_exp;
	int		i;

	buff_exp = NULL;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
			ft_herdoc_expand_dollar(str, &buff_exp, &i, env, exit_status);
		else
			buff_exp = ft_strjoin2(buff_exp, ft_char_to_str(str[i]));
	}
	return (buff_exp);
}

void	ft_open_herdoc(char *eof, t_env *env, int exit_status)
{
	//int	fd_herdoc;
	char	*line;

	//fd_herdoc = open("./.herdoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	//if (fd_herdoc == -1)
	//{
	//	ft_put_error("🍪: error in herdoc file");
	//	return ;
	//}
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp2(line, eof))
		{
			printf("done\n");
			break;
		}
		else 
			printf("%s\n", ft_herdoc_expand(line, env, exit_status));
		free(line);
	}
}


int	main(int ac, char **av, char **ev)
{
	t_env	*env;
	int		exit_status;

	(void)(ac);
	(void)(av);
	env = ft_env_create(ev);
	exit_status = 0;
	ft_open_herdoc("stop", env, exit_status);
	ft_env_clear(&env);
}