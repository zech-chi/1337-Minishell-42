/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:23:31 by zech-chi          #+#    #+#             */
/*   Updated: 2024/04/17 20:04:07 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_execution.h"
#include "../header/minishell_parsing.h"

int	g_signal;

char	*ft_get_prompt(int exit_status)
{
	char	*prompt;

	prompt = readline("🍪🍪🍪>$ ");
	if (prompt && prompt[0])
		add_history(prompt);
	if (!prompt)
	{
		printf("exit\n");
		exit(exit_status);
	}
	return (prompt);
}

void	ft_handle_signals(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 1;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal = 1;
	}
}

static void	ft_init(t_tool *tool, int ac, char **av, char **ev)
{
	tool->grbg = NULL;
	tool->env = ft_env_create(ev);
	tool->err = 0;
	g_signal = 0;
	rl_catch_signals = 0;
	signal(SIGINT, ft_handle_signals);
	signal(SIGQUIT, ft_handle_signals);
	(void)(ac);
	(void)(av);
}

int	main(int ac, char **av, char **ev)
{
	char	*line;
	t_tree	*tree;
	t_tool	tool;

	ft_init(&tool, ac, av, ev);
	if (!isatty(0))
		return (printf("tty required!\n"), 1);
	while (1)
	{
		line = ft_get_prompt(tool.err);
		if (g_signal)
			tool.err = 1;
		tree = parsing_phase(line, &tool);
		ft_execute(tree, &tool.env, &tool.err);
		unlink_heredoc(&tree);
		clear_garbage(tool.grbg);
		tool.grbg = NULL;
		free(line);
		g_signal = 0;
	}
	ft_env_clear(&tool.env);
	rl_clear_history();
	return (SUCCESS);
}
