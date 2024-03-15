/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:40:33 by ymomen            #+#    #+#             */
/*   Updated: 2024/03/15 01:31:37 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"
int	main(void)
{
	char *line;
    t_tree *tree;

	
	while (1)
	{
        err = 0;
		line = readline("🍪\033[0;32m>$ \033[0m");
		add_history(line);
        tree = parsing(line);
        print_tree_2d(tree);
	}
	exit(0);
}
