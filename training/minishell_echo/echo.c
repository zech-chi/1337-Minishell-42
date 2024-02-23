/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:56:25 by zech-chi          #+#    #+#             */
/*   Updated: 2024/02/23 21:38:53 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"

void	ft_print_linked_list(t_list *head)
{
	while (head)
	{
		printf("|%s|\n", head->content);
		head = head->next;
	}
}

// open == 0 or ''' or '"'
t_list	*ft_echo_parse(char *prompt)
{
	t_list	*echo_head;
	char	open;
	char	*cur;
	int		i = 0;
	char	str[2];

	open = 0;
	echo_head = NULL;
	cur = NULL;
	while (prompt[i])
	{
		if (prompt[i] == ' ' && open == 0)
		{
			if (cur)
				ft_lstadd_back(&echo_head, ft_lstnew(cur));
			cur = NULL;
		}
		else if (prompt[i] == '\'')
		{
			cur = ft_strjoin(cur, "'");
			if (open == 0)
				open = '\'';
			else if (open == '\'')
			{
				ft_lstadd_back(&echo_head, ft_lstnew(cur));
				cur = NULL;
				open = 0;
			}
		}
		else if (prompt[i] == '"')
		{
			cur = ft_strjoin(cur, ft_strdup("\""));
			if (open == 0)
				open = '"';
			else if (open == '"')
			{
				ft_lstadd_back(&echo_head, ft_lstnew(cur));
				cur = NULL;
				open = 0;
			}
		}
		else
		{
			str[0] = prompt[i];
			str[1] = 0;
			cur = ft_strjoin(cur, ft_strdup(str));
		}
		i++;
	}
	if (cur)
		ft_lstadd_back(&echo_head, ft_lstnew(cur));
	return (echo_head);
}

int	ft_echo_execute(char *prompt, t_env *env)
{
	char *new_prompt;

	printf("prompt: %s\n", prompt);
	new_prompt = ft_strtrim(prompt, " ");
	printf("new prompt: %s\n", new_prompt);
	if (!ft_strncmp(new_prompt, "echo", 4))
	{
		ft_print_linked_list(ft_echo_parse(new_prompt));
		printf("here\n");
	}
	(void)(env);
	return (0);
}
