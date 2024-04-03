/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_lst_perfix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 00:42:19 by ymomen            #+#    #+#             */
/*   Updated: 2024/04/03 15:28:47 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

void	redarection_join_arg(t_lst **node, t_tool *tool)
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
		else
			cmd = NULL;
		if (is_redarection(cur->type) && cmd && cmd->next && cur->next
			&& cur->next->type == 0)
		{
			hlf = cur->next;
			cmd ->value = ft_strjoin(cmd->value, ft_strdup(" ", tool), tool);
			cmd->value = ft_strjoin(cmd->value, hlf->value, tool);
			cur->next = hlf->next;
		}
		cur = cur->next;
	}
}
