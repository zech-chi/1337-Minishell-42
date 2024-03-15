/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 01:23:32 by ymomen            #+#    #+#             */
/*   Updated: 2024/03/15 01:31:51 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"


t_tree *parsing (char * line)
{
    t_lst *post;
	t_tree *tree;
    t_lst *node;
    
    node = tokens_lst(line);
        // update_lst(&node);
	post = from_infix_to_Postfix(node);
	tree = postfix_tree(post);
	free(post);
	free(node);
	post = NULL;
	node = NULL;
    return (tree);
}

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