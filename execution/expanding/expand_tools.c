/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:48:23 by zech-chi          #+#    #+#             */
/*   Updated: 2024/04/02 00:22:14 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

char	*ft_char_to_str(char c)
{
	char	str[2];

	str[0] = c;
	str[1] = 0;
	return (ft_strdup2(str));
}

char	**ft_lst_to_2d_char(t_list **head)
{
	char	**char_2d;
	int		r;
	t_list	*cur;

	char_2d = (char **)malloc(sizeof(char *) * (ft_lstsize(*head) + 1));
	if (!char_2d)
		return (NULL);
	r = 0;
	cur = *head;
	while (cur)
	{
		char_2d[r] = ft_strdup2(cur->content);
		cur = cur->next;
		r++;
	}
	char_2d[r] = NULL;
	ft_lstclear(head);
	return (char_2d);
}

void	ft_exp_init(t_expand *exp)
{
	exp->buff_exp = NULL;
	exp->buff_env = NULL;
	exp->head = NULL;
	exp->i = -1;
	exp->quote = 0;
	exp->noting_before_quote = 0;
	exp->found_star = 0;
	exp->found_another_char = 0;
}

void	ft_expand_cut(t_expand *exp)
{
	if (exp->buff_exp)
	{
		if (exp->found_star && !exp->found_another_char)
			ft_list_cwd(&(exp->head));
		else
		{
			if (!ft_get_matching(&(exp->head), exp->buff_exp))
				ft_lstadd_back(&(exp->head), ft_lstnew(ft_strdup2(exp->buff_exp)));
		}
		free(exp->buff_exp);
		exp->buff_exp = NULL;
		exp->found_star = 0;
		exp->found_another_char = 0;
		exp->noting_before_quote = 0;
	}
}
