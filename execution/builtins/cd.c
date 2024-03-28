/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:29:33 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/28 21:14:47 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

static void	ft_update_pwd_and_oldpwd(t_env **env)
{
	char	cur_wd[MAXPATHLEN];
	char	*prev_wd;

	prev_wd = ft_env_search(*env, "PWD");
	getcwd(cur_wd, MAXPATHLEN);
	ft_env_delete(env, "OLDPWD");
	ft_env_add(env, ft_strdup2("OLDPWD"), prev_wd, 1);
	ft_env_update(env, ft_strdup2("PWD"), ft_strdup2(cur_wd), 0);
}

static	void	ft_go_to_old_path(t_env **env)
{
	char	*old_pwd;

	old_pwd = ft_env_search(*env, "OLDPWD");
	if (chdir(old_pwd) == SUCCESS)
		ft_update_pwd_and_oldpwd(env);
	else
		ft_put_error("🍪: cd: OLDPWD not set\n");
	free(old_pwd);
}

static	void	ft_go_to_home(t_env **env)
{
	char	*home;

	home = ft_env_search(*env, "HOME");
	if (chdir(home) == SUCCESS)
		ft_update_pwd_and_oldpwd(env);
	free(home);
}

static	void	ft_go_to_new_path(t_env **env, char **cmd_2d)
{
	char	*msg;

	if (chdir(cmd_2d[1]) == SUCCESS)
		ft_update_pwd_and_oldpwd(env);
	else
	{
		msg = ft_strjoin2(ft_strdup2("🍪: cd: "), ft_strdup2(cmd_2d[1]));
		perror(msg);
		free(msg);
	}
}

int	ft_cd(char **cmd_2d, t_env **env)
{
	if (!cmd_2d[1] || !ft_strcmp2("~", cmd_2d[1]))
		ft_go_to_home(env);
	else if (!ft_strcmp2("-", cmd_2d[1]))
		ft_go_to_old_path(env);
	else
		ft_go_to_new_path(env, cmd_2d);
	return (0);
}
