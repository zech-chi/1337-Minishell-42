/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infix_to_postfix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:33:13 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/05 19:45:15 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_v2.h"

void	ft_print_prompt_splited(char **prompt_splited)
{
	int	r;

	r = 0;
	while (prompt_splited[r])
	{
		printf("%s\n", prompt_splited[r]);
		r++;
	}
}

void	ft_parse(char *prompt)
{
	char **prompt_splited;
	int	r;

	prompt_splited = ft_split(prompt, ';');
	if (!prompt_splited)
		exit(1);
	r = 0;
	while (prompt_splited[r])
	{
		prompt_splited[r] = ft_strtrim(prompt_splited[r], " ");
		r++;
	}
	ft_print_prompt_splited(prompt_splited);
}
