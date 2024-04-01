/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 01:23:32 by ymomen            #+#    #+#             */
/*   Updated: 2024/04/01 17:46:55 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

void swap(t_tree **a, t_tree **b)
{
    t_tree *tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}
void fix_tree(t_tree **root)
{
    if (!*root)
        return;
    fix_tree(&(*root)->left);
    fix_tree(&(*root)->right);
    if (is_redarection((*root)->type) && (*root)->left && (*root)->left->type < 0)
    {
        swap(&(*root)->left, &(*root)->right);
    }
}
t_tree *parsing (char * line, t_tool *tool)
{
    t_lst *post;
	t_tree *tree;
    t_lst *node;
    
    node = tokens_lst(line, tool);
	post = from_infix_to_Postfix(node,tool);
    // while(post)
    // {
    //     printf("value: %s its type : %d\n", post->value, post->type);
    //     post = post->next;
    // }
	tree = postfix_tree(post, tool);
	post = NULL;
	node = NULL;
    return (tree);
}

int get_height(t_tree *root) 
{
    if (root == NULL) {
        return 0;
    }
    int left_height = get_height(root->left);
    int right_height = get_height(root->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}

void print_spaces(int n)
{
    for (int i = 0; i < n; i++) {
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
