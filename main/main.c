/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:40:33 by ymomen            #+#    #+#             */
/*   Updated: 2024/03/16 01:30:12 by zech-chi         ###   ########.fr       */
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

//int	main(int ac, char **av, char **ev)
//{
//	t_env	*env;
//	t_node	*root;
//	
//	int	std_in;

//	(void)(ac);
//	(void)(av);
//	(void)(ev);
//	std_in = dup(0);
//	root = ft_build_tree();
//	ft_inorder_traversal(root);
//	printf("-------------- don't look up -----------------\n");
//	printf("----------------------------------------------\n");
//	env = ft_env_create(ev);
//	//ft_env_print(env);
//	exit_status = 0;
//	ft_execute(root, &env, &exit_status);
//	printf("exit_status = %d\n", exit_status);
//	printf("return back\n");
//	//while (1);
//	return (0);
//}


//int	main(int ac, char **av, char **ev)
//{
//	char	*prompt;
//	t_env	*env;
//	char	**p;
//	int		exit_status;

//	(void)(ac);
//	(void)(av);
//	exit_status = 0;
//	env = ft_env_create(ev);
//	while (1)
//	{
//		prompt = ft_get_prompt();
//		if (prompt == NULL)
//		{
//			printf("exit\n");
//			exit(0);
//		}
//		if (prompt[0])
//		{
//			//ft_parse(prompt);
//			//ft_execute(tree);
//			p = ft_expand(prompt, env, exit_status);
//		}
//	}
//	return (0);
//}


int	main(int ac, char **av, char **ev)
{
	t_env	*env;
	char	*line;
	t_tree	*tree;
	int		exit_status;

	(void)(ac);
	(void)(av);
	env = ft_env_create(ev);
	exit_status = 0;
	while (1)
	{
		line = ft_get_prompt(exit_status);
		tree = parsing(line);
		ft_execute(tree, &env, &exit_status);
		//print_tree_2d(tree);
	}
	return (SUCCESS);
}
