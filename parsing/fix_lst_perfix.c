/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_lst_perfix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 00:42:19 by ymomen            #+#    #+#             */
/*   Updated: 2024/04/08 00:52:44 by ymomen           ###   ########.fr       */
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
		else if (cur->type != 0 && !is_redarection(cur->type))
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

int	check_here_doc(char *line, int *fd, char *limiter, t_tool *tool)
{
	if (line && ft_strcmp(line, limiter) == 0)
		return (0);
	if (write(*fd, line, ft_strlen(line)) == -1
		|| write(*fd, "\n", 1) == -1)
	{
		perror(" 🍪: write");
		tool->err = 1;
		return (0);
	}
	return (1);
}
