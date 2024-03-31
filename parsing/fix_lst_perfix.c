/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_lst_perfix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 00:42:19 by ymomen            #+#    #+#             */
/*   Updated: 2024/03/31 02:12:26 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

void	redarection_join_arg(t_lst **node)
{
	t_lst	*cur;
	t_lst	*hlf;
	t_lst	*cmd;

	cmd = NULL;
	cur = *node;
	while (cur)
	{
		if (cur->type == 0 && cur->next && is_redarection(cur->next->type))
			cmd = cur;
		else if (is_redarection(cur->type) && cmd && cmd->next && cur->next
			&& cur->next->type == 0)
		{
			hlf = cur->next;
			cmd ->value = ft_strjoin(cmd->value, ft_strdup(" "));
			cmd->value = ft_strjoin(cmd->value, hlf->value);
			cur->next = hlf->next;
			free(hlf);
			cmd = NULL;
		}
		cur = cur->next;
	}
}

void update_tree(t_tree **root)
{
	char **sp;
	
	if (!*root)
		return ;
	if(is_redarection((*root)->type) && !(*root)->right)
	{
		sp = ft_split2((*root)->value, ' ');
		free((*root)->value);
		(*root)->value = sp[0];
		(*root)->left = new_node(sp[1], -1, 0, -3);
		update_tree(&(*root)->right);
	}
	else
	{
		update_tree(&(*root)->left);
		update_tree(&(*root)->right);
	}
	return;
}