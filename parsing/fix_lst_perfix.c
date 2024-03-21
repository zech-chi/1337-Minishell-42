/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_lst_perfix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 00:42:19 by ymomen            #+#    #+#             */
/*   Updated: 2024/03/21 00:42:32 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

void redarection_join_arg(t_lst **node)
{
	t_lst *cur;
	t_lst *cmd =NULL;
	t_lst *operater = NULL;
	t_lst *hlf;
	cur = *node;
	while (cur)
	{
		if (cur->type == 0 && cur->next && (cur->next->type == INPUT || cur->next->type == REDIRECTION || cur->next->type == APPEND_REDIRECTION || cur->next->type == HERE_DOC))
		{
			cmd = cur;
			operater = cmd->next;
		}
		else if (cur->type < 0 && cmd && operater && cur->next && cur->next->type == 0)
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
void redarection_perfix_lst(t_lst **head)
{
	t_lst *cmd;
	t_lst *red;
	t_lst *node;
	t_lst *prev = NULL;

	node = *head;
	redarection_prac_fix(head);
	while (node)
	{
		if (node->type == 0 && node->next &&(node->next->type == REDIRECTION || node->next->type == INPUT || node->next->type == APPEND_REDIRECTION || node->next->type == HERE_DOC))
		{
			cmd = node;
			red = cmd->next;
			node = red->next;
			if(prev)
				prev->next = cmd->next;
			else
				*head = cmd->next;
			while (node && node->next && (node->next->type < 0 || node->next->type == REDIRECTION || node->next->type == INPUT || node->next->type == APPEND_REDIRECTION || node->next->type == HERE_DOC))
				node = node->next;
			cmd->next = node->next;
			node->next = cmd;
		}
		prev = node;
		node = node->next;
	}
}

void redarection_prac_fix(t_lst **head)
{
	t_lst *node;
	t_lst *open_p = NULL;
	t_lst *close_p = NULL;
	t_lst *prev = NULL;
	t_lst *red = NULL;
	t_lst *red_file = NULL;
	
	node = *head;
	while (node)
	{
		if (node->type == OPEN_PARENTH)
		{
			open_p = node;
			close_p = node->next;
			while (close_p && close_p->type != CLOSE_PARENTH)
				close_p = close_p->next;
			
			if (close_p && close_p ->type == CLOSE_PARENTH && close_p->next && (close_p->next->type == REDIRECTION || close_p->next->type == INPUT || close_p->next->type == APPEND_REDIRECTION || close_p->next->type == HERE_DOC))
			{
				red = close_p->next;
				red_file = red->next;
				while (red_file && red_file->next && (red_file->next->type < 0 || red_file->next->type == REDIRECTION || red_file->next->type == INPUT || red_file->next->type == APPEND_REDIRECTION || red_file->next->type == HERE_DOC))
					red_file = red_file->next;
				close_p->next = red_file->next;
				if (prev)
					prev->next = red;
				else
					*head = red;
				red_file->next = open_p;
			}
		}
		prev = node;
		node = node->next;
	}
}