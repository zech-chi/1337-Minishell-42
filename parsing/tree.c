/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:57:50 by ymomen            #+#    #+#             */
/*   Updated: 2024/03/31 17:28:25 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

t_tree	*new_node(char *value, int prio, int type, int read)
{
	t_tree	*node;
	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);

		node->value = value;
		node->right = NULL;
		node->left = NULL;
		node->prio = prio;
		node->type = type;
		node->read = read;
	return (node);
}