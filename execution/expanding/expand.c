/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:36:52 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/15 19:53:58 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

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
	return (ft_strdup2(str));
}

void	ft_print_lst(t_list *node)
{
	while (node)
	{
		printf("{%s}\n", node->content);
		node = node->next;
	}
}

char	**ft_lst_to_2d_char(t_list *head)
{
	char	**char_2d;
	int		r;

	char_2d = (char **)malloc(sizeof(char *) * (ft_lstsize(head) + 1));
	if (!char_2d)
		return (NULL);
	r = 0;
	while (head)
	{
		char_2d[r] = head->content;
		head = head->next;
		r++;
	}
	char_2d[r] = NULL;
	return (char_2d);
}

char	*ft_list_cwd(t_env *env)
{
	char	*buff;
	DIR		*dir;
	struct	dirent *entry;

	dir = opendir(ft_env_search(env, "PWD"));
	buff = NULL;
	if (dir == NULL)
	{
		perror("Error");
		return (NULL);
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			if (buff)
				buff = ft_strjoin2(buff, ft_strjoin2(" ", entry->d_name));
			else
				buff = ft_strdup2(entry->d_name);
		}
	}
	if (closedir(dir) != 0)
		perror("Error");
	return (buff);
}

void	ft_wild_card(t_list **head, t_env *env)
{
	t_list	*tmp;
	int		i;

	tmp = *head;
	while (tmp)
	{
		i = 0;
		while (((char *)tmp->content)[i] && ((char *)tmp->content)[i] == '*')
			i++;
		if (!((char *)tmp->content)[i])
			tmp->content = ft_list_cwd(env);
		tmp = tmp->next;
	}
}


char **ft_expand(char *prompt, t_env *env, int exit_status)
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
				buff = ft_strjoin2(buff, ft_char_to_str(prompt[i]));
		}
		else if (prompt[i] == '$' && open != '\'')
		{
			while (prompt[i] && prompt[i] == '$')
			{
				buff2 = ft_char_to_str(prompt[i]);
				i++;
				while (prompt[i] && !ft_is_char_in_str(prompt[i], "$, +=?#@*\"'"))
				{
					buff2 = ft_strjoin2(buff2, ft_char_to_str(prompt[i]));
					i++;
				}
				buff = ft_strjoin2(buff, ft_env_search(env, buff2 + 1));
				if (prompt[i] == '?' && ft_strlen2(buff2) == 1)
					buff = ft_strjoin2(buff, ft_itoa2(exit_status));
				else if (prompt[i] == ' ')
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
						buff = ft_strjoin2(buff, ft_char_to_str(prompt[i]));
				}
				else if (prompt[i] && prompt[i] != '$' && prompt[i] != ' ')
					buff = ft_strjoin2(buff, ft_char_to_str(prompt[i]));
				else if (ft_strlen2(buff2) == 1 && !prompt[i])
					buff = ft_strjoin2(buff, buff2);
				buff2 = NULL;
			}
		}
		else
			buff = ft_strjoin2(buff, ft_char_to_str(prompt[i]));

		if (!prompt[i])
			break;
		i++;
	}
	if (buff)
	{
		ft_lstadd_back(&head, ft_lstnew(buff));
		buff = NULL; // free
	}
	//ft_print_lst(head);
	//printf("-------------------------------------------------\n");
	ft_wild_card(&head, env);
	//ft_print_lst(head);
	//printf("-------------------------------------------------\n");
	return (ft_lst_to_2d_char(head));
}
