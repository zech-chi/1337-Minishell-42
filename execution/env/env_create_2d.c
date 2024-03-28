/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create_2d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 20:09:30 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/28 20:09:32 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

char	**ft_env_create_2d(t_env *env)
{
	char	**env_2d;
	int		r;

	env_2d = malloc(sizeof(char *) * (ft_env_size(env) + 1));
	if (!env_2d)
	{
		ft_put_error("🍪: malloc failed\n");
		return (NULL);
	}
	r = 0;
	while (env)
	{
		env_2d[r++] = ft_strjoin2(ft_strdup2(env->key),
				ft_strjoin2(ft_strdup2("="), ft_strdup2(env->value)));
		env = env->next;
	}
	env_2d[r] = NULL;
	return (env_2d);
}
