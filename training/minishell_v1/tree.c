/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:57:50 by ymomen            #+#    #+#             */
/*   Updated: 2024/03/02 18:31:00 by ymomen           ###   ########.fr       */
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


// t_tree	*creat_tree(char *str)
// {
// 	char	*token;
// 	char	dm[3];
// 	t_tree	*node;
	
// 	node = NULL;
// 	token = ft_strtok(str, "()|\"'<>&", dm);
// 	if (token != NULL)
// 	{
// 		if (*dm != '\0')
// 		{
// 			node = new_node(dm);
// 			node->left= new_node(token);
// 			node->right = creat_tree(NULL);
// 		}
// 		else
// 			node->value = ft_strdup(token);
// 		return (node);
// 	}
// 	else
// 		return (NULL);
// }
 
// char **line_parsed(char *str)
// {
// 	char **str;
// 	char s[3];
// 	int i = 0; 
// 	char *token = ft_strtok(str, "()|\"'<>&",s);
// 	while(token!= NULL)
// 	{
// 		token = ft_strtok(NULL, "()|\"'<>&",s);
// 		if (s[0] == '\0' || token == NULL)
// 			break ;
// 		i++;
// 	}
// 	printf("%d", i + i +1);
// }

