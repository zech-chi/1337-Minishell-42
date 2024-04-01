/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 20:23:05 by zech-chi          #+#    #+#             */
/*   Updated: 2024/04/01 21:21:27 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

static void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)b;
	i = 0;
	while (i < len)
		str[i++] = (unsigned char)c;
	return (b);
}

int	ft_is_match(char* s, char* p)
{
	int dp[ft_strlen2(s) + 1][ft_strlen2(p) + 1];
	int s_len = ft_strlen2(s);
	int p_len = ft_strlen2(p);
	int i;
	int j;

	ft_memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	i = -1;
	while (++i <= s_len)
	{
		j = 0;
		while (++j <= p_len)
		{
			if (p[j - 1] == '*')
				dp[i][j] = dp[i][j - 1] | (i > 0 && dp[i - 1][j]);
			else if (i > 0 && (p[j - 1] == s[i - 1] || p[j - 1] == '?'))
				dp[i][j] = dp[i - 1][j - 1];
		}
	}
	return (dp[s_len][p_len]);
}
