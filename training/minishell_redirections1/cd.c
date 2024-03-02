/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:10:02 by zech-chi          #+#    #+#             */
/*   Updated: 2024/02/21 12:32:11 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"

void	ft_pwd_oldpwd_update(t_env **env)
{
	char	cur_wd[MAXPATHLEN];
	char	*prev_wd;

	prev_wd = ft_env_search(*env, "PWD");
	getcwd(cur_wd, MAXPATHLEN);
	ft_env_update(env, "OLDPWD", prev_wd);
	ft_env_update(env, "PWD", ft_strdup(cur_wd));
}

int	ft_cd(char **splited_prompt, t_env **env)
{
	if (!splited_prompt[1] || !ft_strcmp("~", splited_prompt[1]))
	{
		if (chdir(ft_env_search(*env, "HOME")) == SUCCESS)
			ft_pwd_oldpwd_update(env);
	}
	else if (!ft_strcmp("-", splited_prompt[1]))
	{
		if (chdir(ft_env_search(*env, "OLDPWD")) == SUCCESS)
			ft_pwd_oldpwd_update(env);
	}
	else
	{
		if (chdir(splited_prompt[1]) == SUCCESS)
			ft_pwd_oldpwd_update(env);
		else
			perror(ft_strjoin("cookies Error: cd: ", splited_prompt[1]));
	}
	return (0);
}
