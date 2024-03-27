/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:29:33 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/27 21:45:54 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

static void	ft_pwd_oldpwd_update(t_env **env)
{
	char	cur_wd[MAXPATHLEN];
	char	*prev_wd;
	prev_wd = ft_env_search(*env, "PWD");
	getcwd(cur_wd, MAXPATHLEN);
	ft_env_delete(env, "OLDPWD");
	ft_env_add(env, ft_strdup2("OLDPWD"), prev_wd, 1);
	ft_env_update(env, ft_strdup2("PWD"), ft_strdup2(cur_wd), 0);
}

int	ft_cd(char **splited_prompt, t_env **env)
{
	char	*home;
	char	*old_pwd;
	char	*msg;

	if (!splited_prompt[1] || !ft_strcmp2("~", splited_prompt[1]))
	{
		home = ft_env_search(*env, "HOME");
		if (chdir(home) == SUCCESS)
			ft_pwd_oldpwd_update(env);
		free(home);
	}
	else if (!ft_strcmp2("-", splited_prompt[1]))
	{
		old_pwd = ft_env_search(*env, "OLDPWD");
		if (chdir(old_pwd) == SUCCESS)
			ft_pwd_oldpwd_update(env);
		else
			ft_put_error("🍪: cd: OLDPWD not set\n");
		free(old_pwd);
	}
	else
	{
		if (chdir(splited_prompt[1]) == SUCCESS)
			ft_pwd_oldpwd_update(env);
		else
		{
			msg = ft_strjoin2(ft_strdup2("🍪: cd: "), ft_strdup2(splited_prompt[1]));
			perror(msg);
			free(msg);
		}
	}
	return (0);
}
