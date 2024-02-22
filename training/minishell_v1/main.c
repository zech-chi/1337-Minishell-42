/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:40:33 by ymomen            #+#    #+#             */
/*   Updated: 2024/02/22 22:15:33 by ymomen           ###   ########.fr       */
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
		printf("%s\n", here->value);
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
	printf("%s\n", root->value);

	// Process left child
	print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D(t_tree * root)
{
	// Pass initial space count as 0
	print2DUtil(root, 0);
}
int	main(void)
{


	char str[]="(< Makefile grep NAME && < Makefile cat) > out && echo j";
	t_tree *node;
	node = NULL;
	node = creat_tree(str);
	printtrree(node);
	// print2D(node);
		
	
	exit(0);
}
