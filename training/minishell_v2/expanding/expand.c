/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:36:52 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/07 22:21:04 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_v2.h"

// "$;!?*%#"
int	ft_is_char_in_str(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
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
	return (ft_strdup(str));
}

void	ft_print_lst(t_list *node)
{
	while (node)
	{
		printf("{%s}\n", node->content);
		node = node->next;
	}
}

char **ft_expand(char *prompt, t_env *env)
{
	t_list	*head = NULL;
	int open = 0; // " or ' or 0
	char	*buff = NULL;
	int	i = 0;
	char	*buff2 = NULL;

	while (prompt[i])
	{
		if (prompt[i] == ' ' && open == 0)
		{
			if (buff)
			{
				ft_lstadd_back(&head, ft_lstnew(buff));
				buff = NULL; // free
			}
		}
		else if (prompt[i] == '"' || prompt[i] == '\'')
		{
			if (open == 0)
				open = prompt[i];
			else if (open == prompt[i])
				open = 0;
			else
				buff = ft_strjoin(buff, ft_char_to_str(prompt[i]));
		}
		else if (prompt[i] == '$' && open != '\'')
		{
			while (prompt[i] && prompt[i] == '$')
			{
				buff2 = ft_char_to_str(prompt[i]);
				i++;
				while (prompt[i] && !ft_is_char_in_str(prompt[i], "$ +=?#@*\"'"))
				{
					buff2 = ft_strjoin(buff2, ft_char_to_str(prompt[i]));
					i++;
				}
				buff = ft_strjoin(buff, ft_env_search(env, buff2 + 1));
				if (prompt[i] == '"' || prompt[i] == '\'')
				{
					if (open == 0)
						open = prompt[i];
					else if (open == prompt[i])
						open = 0;
					else
						buff = ft_strjoin(buff, ft_char_to_str(prompt[i]));
				}
				else if (prompt[i] && prompt[i] != '$' && prompt[i] != ' ')
					buff = ft_strjoin(buff, ft_char_to_str(prompt[i]));
				buff2 = NULL;
			}
		}
		else
			buff = ft_strjoin(buff, ft_char_to_str(prompt[i]));

		if (!prompt[i])
			break;
		i++;
	}
	if (buff)
	{
		ft_lstadd_back(&head, ft_lstnew(buff));
		buff = NULL; // free
	}
	ft_print_lst(head);
	return (NULL);
}
