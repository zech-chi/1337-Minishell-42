/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:03:03 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/21 01:27:28 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

int	ft_execute_builtins(char **cmd_2d, t_env **env, int *exit_status)
{
	if (!cmd_2d || !(*cmd_2d))
		return (SUCCESS);
	else if (!ft_strcmp2("env", cmd_2d[0]))
		return (ft_env_print(*env), *exit_status = 0, SUCCESS);
	else if (!ft_strcmp2("exit", cmd_2d[0]))
		return (ft_exit(cmd_2d, env, exit_status), SUCCESS);
	else if (!ft_strcmp2("echo", cmd_2d[0]))
		return (ft_echo(cmd_2d), *exit_status = 0, SUCCESS);
	else if (!ft_strcmp2("cd", cmd_2d[0]))
		return (ft_cd(cmd_2d, env), *exit_status = 0, SUCCESS);
	else if (!ft_strcmp2("export", cmd_2d[0]))
		return (ft_export(env, cmd_2d), *exit_status = 0, SUCCESS);
	else if (!ft_strcmp2("pwd", cmd_2d[0]))
		return (ft_pwd_print(), *exit_status = 0, SUCCESS);
	else if (!ft_strcmp2("unset", cmd_2d[0]))
		return (ft_unset(env, cmd_2d), *exit_status = 0, SUCCESS);
	else
		return (FAILED);
}
