/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:57:50 by ymomen            #+#    #+#             */
/*   Updated: 2024/04/01 14:43:58 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

t_tree	*new_node(char *value, int prio, int type, t_tool *tool)
{
	t_tree	*node;
	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	add_to_grbg(&tool->grbg, node);	
	node->value = value;
	node->right = NULL;
	node->left = NULL;
	node->prio = prio;
	node->type = type;
	return (node);
}
void unlink_heredoc(t_tree **root)
{
	char **sp;
	
	if (!*root)
		return ;
	if((*root)->type == HERE_DOC && !access((*root)->left->value, F_OK))
	{
		unlink((*root)->left->value);
		unlink_heredoc(&(*root)->right);
	}
	else
	{
		unlink_heredoc(&(*root)->left);
		unlink_heredoc(&(*root)->right);
	}
	return;
}