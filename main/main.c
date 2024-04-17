/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:23:31 by zech-chi          #+#    #+#             */
/*   Updated: 2024/04/17 16:14:06 by ymomen           ###   ########.fr       */
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
	}
}

// original main
void dd()
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **ev)
{
	char	*line;
	t_tree	*tree;
	t_tool	tool;

	(void)(ac);
	(void)(av);
	tool.grbg = NULL;
	tool.env = ft_env_create(ev);
	tool.err = 0;
	rl_catch_signals = 0;
	signal(SIGINT, ft_handle_signals);
	signal(SIGQUIT, ft_handle_signals);
		g_signal = 0;
	while (1)
	{
		line = ft_get_prompt(tool.err);
		if(g_signal == 1)
			tool.err = 1;
		tree = parsing_phase(line, &tool);
		//printf("--------------- tree --------------------\n");
		//print_tree_2d(tree);
		//printf("-----------------------------------------\n");
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
