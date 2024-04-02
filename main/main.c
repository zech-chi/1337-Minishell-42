/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:23:31 by zech-chi          #+#    #+#             */
/*   Updated: 2024/04/02 01:31:59 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_execution.h"
#include "../header/minishell_parsing.h"

char	*ft_get_prompt(int exit_status)
{
	char	*prompt;

	if (exit_status == 0)
		prompt = readline("🍪🍪🍪"GREEN_COLOR">$ "RESET_COLOR);
	else
		prompt = readline("🍪🍪🍪"RED_COLOR">$ "RESET_COLOR);
	if (prompt && prompt[0])
		add_history(prompt);
	return (prompt);
}

/*
	ft_env_clear(&env);
	ft_free_2d_char(cmd_2d);
	free(line);
*/
// original main
void dd()
{system("leaks minishell");}
int	main(int ac, char **av, char **ev)
{
	char	*line;
	t_tree	*tree;
	t_tool	tool;

	//signal()
	(void)(ac);
	(void)(av);
	tool.grbg = NULL;
	tool.env = ft_env_create(ev);
	tool.err = 0;
	while (1)
	{
		 dd();
		line = ft_get_prompt(tool.err);
		tree = parsing(line, &tool);
		printf("--------------- tree --------------------\n");
		print_tree_2d(tree);
		printf("-----------------------------------------\n");
		ft_execute(tree, &tool.env, &tool.err);
		printf("-----------------------------------------\n");
		clear_garbage(tool.grbg);
		tool.grbg = NULL;
		free(line);
	}
	rl_clear_history();
	return (SUCCESS);
}

