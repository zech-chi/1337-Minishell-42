/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:25:40 by zech-chi          #+#    #+#             */
/*   Updated: 2024/02/25 17:27:30 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"

int	status = 0;

int	ft_execute_builtins(char **splited_prompt, t_env **env)
{
	if (!splited_prompt || !(*splited_prompt))
		return (SUCCESS);
	else if (!ft_strcmp(ENV, splited_prompt[0]))
		return (ft_env_print(*env), SUCCESS);
	else if (!ft_strcmp(EXIT, splited_prompt[0]))
		return (printf("exit\n") ,exit(SUCCESS), SUCCESS);
	else if (!ft_strcmp(PWD, splited_prompt[0]))
		return (ft_pwd_print(), SUCCESS);
	else if (!ft_strcmp(CD, splited_prompt[0]))
		return (ft_cd(splited_prompt, env));
	else if (!ft_strcmp(EXPORT, splited_prompt[0]))
		return (ft_export(env, splited_prompt));
	else if (!ft_strcmp(UNSET, splited_prompt[0]))
		return (ft_unset(env, splited_prompt));
	else if (!ft_strcmp("echo", splited_prompt[0]) && !ft_strcmp("$?", splited_prompt[1]))
		return (printf("%d\n", status % 255), 0);
	else
		return (FAILED); 
}

void	ft_execute_3(char **splited_prompt, t_env *env)
{
	char	**path;
	char	*command;
	int		r;

	command = splited_prompt[0];
	path = ft_split(ft_env_search(env, "PATH"), ':');
	if (!path)
		return ;
	r = -1;
	while (path[++r])
		execve(ft_strjoin(path[r], ft_strjoin("/", command)), splited_prompt, ft_env_create_2d(env));
}

void	ft_execute(char *prompt, t_env **env, int redirections, char *file_path)
{
	char	**splited_prompt;
	pid_t	pid;
	int		fd;

	fd = -1;
	if (redirections != 0)
	{
		if (redirections == 1)
			fd = open(ft_strtrim(file_path, " "), O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redirections == 2)
			fd = open(ft_strtrim(file_path, " "), O_WRONLY | O_CREAT | O_APPEND, 0644);

		if (fd == -1)
			perror("open");
	}

	splited_prompt = ft_split(prompt, SPACE);
	if (ft_execute_builtins(splited_prompt, env) == SUCCESS)
		return ;
	pid = fork();
	if (pid == 0)
	{
		if (fd != -1)
		{
			if (dup2(fd, 1) == -1)
			{
				perror("dup2");
				close(fd);
				return ;
			}
		}
		execve(splited_prompt[0], splited_prompt, ft_env_create_2d(*env));
		ft_execute_3(splited_prompt, *env);
		perror("cookies error");
		exit(errno);
	}
	else if (pid > 0)
	{
		wait(&status);
		if (fd != -1)
			close(fd);
	}
	else
		perror("can't fork");

	if (fd != -1)
		close(fd);
}
