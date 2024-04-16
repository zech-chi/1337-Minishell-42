/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:29:33 by zech-chi          #+#    #+#             */
/*   Updated: 2024/04/16 17:39:33 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d;
	size_t	s;
	size_t	dst_len;
	size_t	src_len;

	if (dst == NULL && dstsize == 0)
		return (0);
	dst_len = ft_strlen2(dst);
	src_len = ft_strlen2(src);
	if (dst_len >= dstsize)
		return (src_len + dstsize);
	d = dst_len;
	s = 0;
	while (src[s] && d < dstsize - 1)
	{
		dst[d] = src[s];
		d++;
		s++;
	}
	dst[d] = '\0';
	return (dst_len + src_len);
}

static void	ft_update_pwd_and_oldpwd(t_env **env, char *prev_wd)
{
	char	cwd[MAXPATHLEN];
	char	*cwd_key;
	char	*cwd_value;

	ft_env_delete(env, "OLDPWD");
	ft_env_add(env, ft_strdup2("OLDPWD"), prev_wd, 1);
	if (getcwd(cwd, MAXPATHLEN) == NULL)
	{
		perror("cd: error retrieving current directory: \
		getcwd: cannot access parent directories");
	}
	cwd_value = ft_get_cwd();
	cwd_key = ft_strdup2("PWD");
	if (ft_env_update(env, cwd_key, cwd_value, 0))
	{
		free(cwd_key);
		free(cwd_value);
	}
}

static	void	ft_go_to_old_path(t_env **env, int *exit_status)
{
	char	*old_pwd;
	char	*prev_wd;

	prev_wd = ft_get_cwd();
	old_pwd = ft_env_search(*env, "OLDPWD");
	if (chdir(old_pwd) == SUCCESS)
	{
		ft_update_pwd_and_oldpwd(env, prev_wd);
		*exit_status = 0;
	}
	else
	{
		ft_put_error("🍪: cd: OLDPWD not set\n");
		*exit_status = 1;
		free(prev_wd);
	}
	free(old_pwd);
}

static	void	ft_go_to_home(t_env **env, int *exit_status)
{
	char	*home;
	char	*prev_wd;

	prev_wd = ft_get_cwd();
	home = ft_env_search(*env, "HOME");
	if (!home)
		ft_put_error("🍪: cd: HOME not set\n");
	if (chdir(home) == SUCCESS)
	{
		ft_update_pwd_and_oldpwd(env, prev_wd);
		*exit_status = 0;
	}
	else
	{
		*exit_status = 1;
		free(prev_wd);
	}
	free(home);
}

static	void	ft_go_to_new_path(t_env **env, char **cmd_2d, int *exit_status)
{
	char	*msg;
	char	*prev_wd;

	prev_wd = ft_get_cwd();
	if (chdir(cmd_2d[1]) == SUCCESS)
	{
		ft_update_pwd_and_oldpwd(env, prev_wd);
		*exit_status = 0;
	}
	else
	{
		msg = ft_strjoin2(ft_strdup2("🍪: cd: "), ft_strdup2(cmd_2d[1]));
		perror(msg);
		free(msg);
		free(prev_wd);
		*exit_status = 1;
	}
}

int	ft_cd(char **cmd_2d, t_env **env, int *exit_status)
{
	if (!cmd_2d[1] || !ft_strcmp2("~", cmd_2d[1]))
		ft_go_to_home(env, exit_status);
	else if (!ft_strcmp2("-", cmd_2d[1]))
		ft_go_to_old_path(env, exit_status);
	else
		ft_go_to_new_path(env, cmd_2d, exit_status);
	return (0);
}
