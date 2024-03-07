/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 22:09:34 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/07 17:25:45 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_v2.h"

t_node	*ft_create_node(char *data, int index, int	type)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->data = data;
	new_node->index = index;
	new_node->type = type;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

t_node	*ft_insert_node(t_node *root, char *data, int index, int type)
{
	if (!root)
		root = ft_create_node(data, index, type);
	else
	{
		if (root->index >= index)
			root->left = ft_insert_node(root->left, data, index, type);
		else
			root->right = ft_insert_node(root->right, data, index, type);
	}
	return (root);
}

void	ft_inorder_traversal(t_node *root)
{
	if (root)
	{
		ft_inorder_traversal(root->left);
		printf("index (%d) type (", root->index);
		if (root->type == CMD)
			printf("CMD");
		else if (root->type == PIPE)
			printf("PIPE");
		else if (root->type == AND)
			printf("AND");
		else if (root->type == OR)
			printf("OR");
		else if (root->type == REDIRECT_OUTPUT)
			printf("REDIRECT_OUTPUT");
		else if (root->type == REDIRECT_OUTPUT_APPEND)
			printf("REDIRECT_OUTPUT_APPEND");
		else if (root->type == REDIRECT_INPUT)
			printf("REDIRECT_INPUT");
		else if (root->type == HEREDOC)
			printf("HEREDOC");
		printf(") --> `%s`\n", root->data);
		ft_inorder_traversal(root->right);
	}
}

t_node	*ft_build_tree(void)
{
	t_node	*root;

	root = NULL;
	//root = ft_insert_node(root, ft_strdup("||"), 4, OR);
	root = ft_insert_node(root, ft_strdup("|"), 2, PIPE);
	root = ft_insert_node(root, ft_strdup("cat"), 1, CMD);
	root = ft_insert_node(root, ft_strdup("ls"), 3, CMD);
	//root = ft_insert_node(root, ft_strdup("ls"), 5, CMD);
	return (root);
}
