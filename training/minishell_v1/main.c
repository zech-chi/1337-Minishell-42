/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:40:33 by ymomen            #+#    #+#             */
/*   Updated: 2024/03/07 21:42:57 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"

int get_height(t_tree *root) {
    if (root == NULL) {
        return 0;
    }
    int left_height = get_height(root->left);
    int right_height = get_height(root->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}

// Function to print spaces for formatting
void print_spaces(int n) {
    for (int i = 0; i < n; i++) {
        printf(" ");
		fflush(stdout);
    }
}

// Recursive function to print the tree in 2D
void print_tree_2d_util(t_tree *root, int level, int space) {
    if (root == NULL) {
        return;
    }

    // Increase space for next level
    space += level;

    // Process right child first for right-angled tree (in-order traversal)
    print_tree_2d_util(root->right, level, space);

    // Print current node after padding
    print_spaces(space);
    printf("%s\n", root->value);
	fflush(stdout);

    // Process left child
    print_tree_2d_util(root->left, level, space);
}

// Function to print the tree in 2D
void print_tree_2d(t_tree *root) {
    int height = get_height(root);
    print_tree_2d_util(root, height, 0);
}

int	main(void)
{
	char *line;
	t_lst *node;
	t_lst *post = NULL;
	t_tree *tree;
	node = NULL;
	// atexit(ff);
	while (1)
	{
		line = readline("🍪🍪🍪\033[0;32m>$ \033[0m");
		node = tokens_lst(line);
		post = from_infix_to_Postfix(node);
		tree = postfix_tree(post);
		print_tree_2d(tree);
	// while (post)
	// {
	// 	printf("%s\n", post->value);
	// 	post = post->next;
	// }
	free(post);
	free(node);
	post = NULL;
	free(tree);
	tree = NULL;
	node = NULL;
	}
	exit(0);
}
