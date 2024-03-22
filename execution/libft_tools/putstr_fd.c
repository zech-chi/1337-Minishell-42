/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:44:19 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/21 01:46:08 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

void	ft_putstr_fd2(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	write(fd, s, ft_strlen2(s));
}
