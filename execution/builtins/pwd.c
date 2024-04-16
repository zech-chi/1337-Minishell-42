/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:43:16 by zech-chi          #+#    #+#             */
/*   Updated: 2024/04/16 17:40:05 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

char	*ft_get_cwd(void)
{
	char		cwd[MAXPATHLEN];
	static char	save_cwd[MAXPATHLEN];

	if (getcwd(cwd, MAXPATHLEN) != NULL)
		ft_strlcpy2(save_cwd, cwd, MAXPATHLEN);
	return (ft_strdup2(save_cwd)); // must free
}

void	ft_pwd_print(void)
{
	char	*cwd;

	cwd = ft_get_cwd();
	printf("%s\n", cwd);
	free(cwd);
}
