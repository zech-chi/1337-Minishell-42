/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:36:52 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/06 09:57:30 by zech-chi         ###   ########.fr       */
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

char	**ft_expand(char *prompt)
{
	t_list	*expanded_prompt;	// store expanded prompt
	int		open;	//store " or ' or space 
	int		i;	// index in prompt
	char	*cur;	// store small part part of prompt
	char	*env_var;	// store if found $ to look in env after
	int		op;

	if (!prompt)
		return (0);
	open = 0;
	i = -1;
	cur = NULL;
	expanded_prompt = NULL;
	env_var = NULL;
	op = 0;
	while (prompt[++i])
	{
		if (prompt[i] == ' ' && open == 0)
		{
			if (cur)
			{
				ft_lstadd_back(&expanded_prompt, ft_lstnew(cur));
				cur = NULL; // I must call free
			}
		}
		else if (prompt[i] == '"' || prompt[i] == '\'')
		{
			if (open == 0)
				open = prompt[i];
			else if (open == prompt[i])
				open = 0;
			else
				cur = ft_strjoin(cur, ft_char_to_str(prompt[i]));
		}
		else if (prompt[i] == '$' && open != '\'')
		{
			env_var = ft_strjoin(env_var, ft_char_to_str(prompt[i]));
			op = 1;
		}
		else
			cur = ft_strjoin(cur, ft_char_to_str(prompt[i]));
	}
	if (cur)
		ft_lstadd_back(&expanded_prompt, ft_lstnew(cur));
	ft_print_lst(expanded_prompt);
	return (NULL);
}
