/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:37:53 by zech-chi          #+#    #+#             */
/*   Updated: 2024/02/25 18:48:38 by zech-chi         ###   ########.fr       */
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

int	main(int ac, char **av, char **ev)
{
	char	*prompt;
	t_env	*env;

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
		//ft_echo_execute(prompt, env);
	}
	return (SUCCESS);
}
