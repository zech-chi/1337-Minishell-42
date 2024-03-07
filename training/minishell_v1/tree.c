/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:57:50 by ymomen            #+#    #+#             */
/*   Updated: 2024/03/06 13:32:48 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"

t_tree	*new_node(char *value)
{
	t_tree	*node;
	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);

		node->value = value;
		node->right = NULL;
		node->left = NULL;
	return (node);
}
t_tree* insertIntoBST(t_tree* root, char *value) 
{
   if (!root)
        return (new_node(value));
    else
    {
        if (root->value < value)
            root -> right = insertIntoBST(root->right, value);
        else if (root->value > value)
           root->left = insertIntoBST(root->left, value);
    }
    return (root);
}