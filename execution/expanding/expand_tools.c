/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:48:23 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/27 22:12:27 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

int	ft_is_delimiter(char c)
{
	int	i;

	i = 0;
	while (DELIMITERS[i])
	{
		if (DELIMITERS[i] == c)
			return (1);
		i++;
	}
	return (0);
}

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

void	ft_list_cwd(t_list **head)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (dir == NULL)
	{
		perror("Error");
		return ;
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
			ft_lstadd_back(head, ft_lstnew(ft_strdup2(entry->d_name)));
		entry = readdir(dir);
	}
	if (closedir(dir) != 0)
		perror("Error");
}

void	ft_exp_init(t_expand *exp)
{
	exp->buff_exp = NULL;
	exp->buff_env = NULL;
	exp->cmd_2d = NULL;
	exp->head = NULL;
	exp->i = -1;
	exp->quote = 0;
	exp->noting_before_quote = 0;
	exp->noting_before_env_var = 1;
	exp->found_star = 0;
	exp->found_another_char = 0;
}
