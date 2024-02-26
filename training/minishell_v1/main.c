/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:40:33 by ymomen            #+#    #+#             */
/*   Updated: 2024/02/26 15:52:34 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"
#define COUNT 10
void ff()
{system("leaks a.out");}
void printtrree(t_tree *here)
{
	if(here)
	{
		printtrree(here->left);
		printf("%d\n", here->indx);
		printtrree(here->right);
	}
	return;
}
void print2DUtil(t_tree * root, int space)
{
	// Base case
	if (root == NULL)
		return;

	// Increase distance between levels
	space += COUNT;

	// Process right child first
	print2DUtil(root->right, space);

	// Print current node after space
	// count
	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	printf("%d\n", root->indx);

	// Process left child
	print2DUtil(root->left, space);
}
void print2D(t_tree * root)
{
	// Pass initial space count as 0
	print2DUtil(root, 0);
}
int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}
int	main(void)
{


	char *line;
	t_lst *node;
	node = NULL;
	// char s[3];
	// int i = 0;
	atexit(ff);
	
	while (1)
	{
		line = readline("🍪🍪🍪\033[0;32m>$ \033[0m");
		node = tokens_lst(line);
		char **arr = lst_to_arr(node);
		int k  = 0;
		
		while(*arr)
		{
			 k = 0;
			while (*arr[k])
			{
		
					
			}
			printf("%s\n",*arr);
			arr++;
		}
		free(line);
	}
	
	exit(0);
}
