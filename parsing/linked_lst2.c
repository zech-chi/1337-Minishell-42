/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lst2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:27:36 by ymomen            #+#    #+#             */
/*   Updated: 2024/03/16 07:39:13 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

void	ft_lstadd_front(t_lst **lst, t_lst *new)
{
	new->next = *lst;
	*lst = new;
}

t_lst	*lastone(t_lst *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	is_operateur(t_lst **node)
{
	if (!*node)
		return ;
	if (!ft_strcmp((*node)->value, "("))
	{
		(*node)->prio = open_par;
		(*node)->type = OPEN_PARENTH;
		(*node)->read = (L_TO_R);
	}
	else if (!ft_strcmp((*node)->value, ")"))
	{
		(*node)->prio = close_par;
		(*node)->type = CLOSE_PARENTH;
		(*node)->read = (R_TO_L);
	}
	else if (!ft_strcmp((*node)->value, "&&"))
	{
		(*node)->prio = (and);
		(*node)->type = AND;
		(*node)->read = (R_TO_L);
	}
	else if (!ft_strcmp((*node)->value, "||"))
	{
		(*node)->prio = (or);
		(*node)->type = OR;
		(*node)->read = (R_TO_L);
	}
	else if (!ft_strcmp((*node)->value, "|"))
	{
		(*node)->prio = (pip);
		(*node)->type = PIPE;
		(*node)->read = (L_TO_R);
	}
	else if (!ft_strcmp((*node)->value, ">"))
	{
		(*node)->prio = (redir);
		(*node)->type = REDIRECTION;
		(*node)->read = (L_TO_R);
	}
	else if (!ft_strcmp((*node)->value, ">>"))
	{
		(*node)->prio = (appand);
		(*node)->type = APPEND_REDIRECTION;
		(*node)->read = (L_TO_R);
	}
	else if (!ft_strcmp((*node)->value, "<<"))
	{
		(*node)->prio = (here_doc);
		(*node)->type = HERE_DOC;
		(*node)->read = (L_TO_R);
	}
	else if (!ft_strcmp((*node)->value, "<"))
	{
		(*node)->prio = (input);
		(*node)->type = INPUT;
		(*node)->read = (L_TO_R);
	}
	else
	{
		(*node)->prio = -1;
		(*node)->type = 0;
		(*node)->read = -1;
	}
}

void	init_type(t_lst *prev, t_lst *node)
{
	if (prev && node)
	{
		if (prev->type == REDIRECTION)
			{
				node->read = L_TO_R;
				node->type = OUTFILE;
			}
		else if (prev->type == INPUT)
			{
				node->read = L_TO_R;
				node->type = INFILE;
			}
		else if (prev->type == APPEND_REDIRECTION)
			{
				node->read = L_TO_R;
				node->type = OUTFILE_APPAND;
			}
		else if (prev->type == HERE_DOC)
			{
				node->read = L_TO_R;
				node->type = LIMITER;
			}
		else
			 if (node->type == 0)
			 {
                node->type = OPERAND;
                node->prio = 0;
                node->read = R_TO_L; 
			 }
	}
}

void redarection_join_arg(t_lst **node)
{
	t_lst *cur;
	t_lst *cmd =NULL;
	t_lst *operater = NULL;
	char *tmp;
	cur = *node;
	while (cur)
	{
		if (cur->type == 0 && cur->next && cur->next->type > 0)
		{
			cmd = cur;
			operater = cmd->next;
		}
		else if (cur->type < 0 && cmd && operater && operater->type> 0)
		{
			t_lst *hlf = cur->next;
			if (hlf && hlf->type == 0)
			{
				tmp = cmd->value;
				cmd ->value = ft_strjoin(cmd->value, ft_strdup(" "));
				cmd->value = ft_strjoin(cmd->value, hlf->value);
				cur->next = hlf->next;
				free(hlf);
			}
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
