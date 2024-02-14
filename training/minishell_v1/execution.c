/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:25:40 by zech-chi          #+#    #+#             */
/*   Updated: 2024/02/14 18:16:45 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"

int	ft_execute_builtins(char **splited_prompt, t_env *env)
{
	if (!splited_prompt || !(*splited_prompt))
		return (SUCCESS);
	else if (!ft_strcmp(ENV, splited_prompt[0]))
		return (ft_env_print(env), SUCCESS);
	else if (!ft_strcmp(EXIT, splited_prompt[0]))
		return (printf("exit\n") ,exit(SUCCESS), SUCCESS);
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

void	ft_execute(char *prompt, t_env **env)
{
	char	**splited_prompt;
	pid_t	pid;

	splited_prompt = ft_split(prompt, SPACE);
	if (ft_execute_builtins(splited_prompt, *env) == SUCCESS)
		return ;
	pid = fork();
	if (pid == 0)
	{
		execve(splited_prompt[0], splited_prompt, ft_env_create_2d(*env));
		ft_execute_3(splited_prompt, *env);
		perror("cookies error");
		exit(SUCCESS);
	}
	else if (pid > 0)
		wait(NULL);
	else
		perror("can't fork");
}
