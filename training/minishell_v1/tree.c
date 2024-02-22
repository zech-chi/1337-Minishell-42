/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:57:50 by ymomen            #+#    #+#             */
/*   Updated: 2024/02/22 22:10:00 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"

t_tree	*new_node(char *str)
{
	t_tree	*node;
	char	*value;

	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	value = ft_strdup(str);
	if (value)
	{
		node->value = value;
		node->right = NULL;
		node->left = NULL;
	}
	else
	{
		free(node);
		return (NULL);
	}
	return (node);
}

t_tree	*creat_tree(char *str)
{
	char	*token;
	char	dm[3];
	t_tree	*node;
	
	node = NULL;
	token = ft_strtok(str, "()|\"'<>&", dm);
	if (token != NULL)
	{
		if (*dm != '\0')
		{
			node = new_node(dm);
			node->left= new_node(token);
			node->right = creat_tree(NULL);
		}
		else
			node->value = ft_strdup(token);
		return (node);
	}
	else
		return (NULL);
}
 
