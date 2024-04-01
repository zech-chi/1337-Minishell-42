/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:43:16 by zech-chi          #+#    #+#             */
/*   Updated: 2024/04/01 00:23:49 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

void	ft_pwd_print(void)
{
	char	buff[MAXPATHLEN];

	printf("%s\n", getcwd(buff, MAXPATHLEN));
}
