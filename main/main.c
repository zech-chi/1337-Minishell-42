/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:23:31 by zech-chi          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/01 21:50:16 by zech-chi         ###   ########.fr       */
=======
/*   Updated: 2024/04/01 20:28:22 by ymomen           ###   ########.fr       */
>>>>>>> 7928b9b09521ef624a5870245578c10723abcfbd
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
<<<<<<< HEAD
		line = ft_get_prompt(exit_status);
		tree = parsing(line, &exit_status);
		//printf("--------------- tree --------------------\n");
		//print_tree_2d(tree);
		//printf("-----------------------------------------\n");
		//if (tree)
		//	printf("%d\n", tree->type);
		ft_execute(tree, &env, &exit_status);
=======
		// dd();
		line = ft_get_prompt(tool.err);
		tree = parsing(line, &tool);
		printf("--------------- tree --------------------\n");
		print_tree_2d(tree);
		printf("-----------------------------------------\n");
		ft_execute(tree, &tool.env, &tool.err);
		clear_garbage(tool.grbg);
		tool.grbg = NULL;
>>>>>>> 7928b9b09521ef624a5870245578c10723abcfbd
		free(line);
	}
	rl_clear_history();
	return (SUCCESS);
}

