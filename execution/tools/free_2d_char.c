/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2d_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:44:48 by zech-chi          #+#    #+#             */
/*   Updated: 2024/04/02 00:53:39 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

void	ft_free_2d_char(char **char_2d)
{
	int	r;

	if (!char_2d)
		return ;
	r = 0;
	while (char_2d[r])
	{
		free(char_2d[r]);
		r++;
	}
	free(char_2d);
	char_2d = NULL;
}
