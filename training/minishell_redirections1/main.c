/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:37:53 by zech-chi          #+#    #+#             */
/*   Updated: 2024/02/25 18:35:04 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"

// this function ask user to enter prompt
// and if prompt not NULL it add it to history
char	*ft_get_prompt()
{
	char	*prompt;

	prompt = readline("🍪🍪🍪\033[0;32m>$ \033[0m");
	if (prompt && prompt[0])
		add_history(prompt);
	return (prompt);
}



int	ft_is_char_in_str(char *str, char c)
{
	int count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

int	main(int ac, char **av, char **ev)
{
	char	*prompt;
	t_env	*env;
	int		redirections;
	char	**splited;

	(void)(ac);
	(void)(av);
	env = ft_env_create(ev);
	while (1)
	{
		prompt = ft_get_prompt();
		if (prompt == NULL)
		{
			printf("exit\n");
			exit(SUCCESS);
		}
		//redirections = ft_is_char_in_str(prompt, '>');
		//if (redirections == 0)
		//	ft_execute(prompt, &env, 0, NULL);
		//else
		//{
		//	splited = ft_split(prompt, '>');
		//	if (redirections == 1)
		//		ft_execute(splited[0], &env, 1, splited[1]);
		//	else if (redirections == 2)
		//		ft_execute(splited[0], &env, 2, splited[1]);
		//}
	}
	return (SUCCESS);
}
