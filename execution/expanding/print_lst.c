/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:21:12 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/16 17:22:11 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

void	ft_print_lst(t_list *node)
{
	while (node)
	{
		printf("{%s}\n", node->content);
		node = node->next;
	}
}
