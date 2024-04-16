/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:57:50 by ymomen            #+#    #+#             */
/*   Updated: 2024/04/15 14:55:18 by ymomen           ###   ########.fr       */
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

void	unlink_heredoc(t_tree **root)
{
	if (!*root)
		return ;
	if ((*root)->type == HERE_DOC && !access((*root)->left->value, F_OK))
	{
		unlink((*root)->left->value);
		unlink_heredoc(&(*root)->right);
	}
	else
	{
		unlink_heredoc(&(*root)->left);
		unlink_heredoc(&(*root)->right);
	}
	return ;
}

char	*ft_split_first(char *str, char delimiter, t_tool *tool)
{
	int		i;
	char	*ptr;

	i = 0;
	while (str[i] && str[i] != delimiter)
		i++;
	ptr = ft_monstrdup(str, i, tool);
	return (ptr);
}

void	update_tree(t_tree **root, t_tool *tool)
{
	char	*sp;

	if (!*root)
		return ;
	if (is_redarection((*root)->type) && !(*root)->left)
	{
		sp = ft_split_first((*root)->value, ' ', tool);
		if (!sp)
		{
			root = NULL;
			return ;
		}
		(*root)->left = new_node(ft_monstrdup(&(*root)->value[ft_strlen(sp)],
					ft_strlen((*root)->value) - ft_strlen(sp), tool),
				-1, -2, tool);
		(*root)->value = sp;
		update_tree(&(*root)->right, tool);
	}
	else
	{
		update_tree(&(*root)->left, tool);
		update_tree(&(*root)->right, tool);
	}
	return ;
}
