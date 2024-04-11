/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 01:23:32 by ymomen            #+#    #+#             */
/*   Updated: 2024/04/11 15:28:33 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

t_tree	*parsing_phase(char *line, t_tool *tool)
{
	t_lst	*post;
	t_tree	*tree;
	t_lst	*node;

	node = tokens_lst(line, tool);
	post = from_infix_to_postfix(node, tool);
	tree = postfix_tree(post, tool);
	update_tree(&tree, tool);
	post = NULL;
	node = NULL;
	return (tree);
}

int	get_height(t_tree *root)
{
	int	left_height;
	int	right_height;

	if (root == NULL)
		return (0);
	left_height = get_height(root->left);
	right_height = get_height(root->right);
	return (1 + (left_height > right_height ? left_height : right_height));
}

void	print_spaces(int n)
{
	for (int i = 0; i < n; i++)
	{
        printf(" ");
		fflush(stdout);
    }
}

void print_tree_2d_util(t_tree *root, int level, int space)
{
    if (root == NULL) {
        return;
    }
    space += level;
    print_tree_2d_util(root->right, level, space);
    print_spaces(space);
    printf("%s\n", root->value);
	fflush(stdout);
    print_tree_2d_util(root->left, level, space);
}

void print_tree_2d(t_tree *root)
{
    int height = get_height(root);
    print_tree_2d_util(root, height, 0);
}
