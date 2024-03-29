/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 22:01:06 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/29 01:49:31 by zech-chi         ###   ########.fr       */
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
//original main

void	ft_sighandle(int sig)
{
	printf("%d\n", sig);
}

int	main(int ac, char **av, char **ev)
{
	t_env	*env;
	char	*line;
	t_tree	*tree;
	int		exit_status;

	//signal()
	(void)(ac);
	(void)(av);
	env = ft_env_create(ev);
	exit_status = 0;
	while (1)
	{
		line = ft_get_prompt(exit_status);
		tree = parsing(line, &exit_status);
		//printf("--------------- tree --------------------\n");
		//print_tree_2d(tree);
		//printf("-----------------------------------------\n");
		//if (tree)
		//	printf("%d\n", tree->type);
		ft_execute(tree, &env, &exit_status);
		free(line);
	}
	return (SUCCESS);
}
