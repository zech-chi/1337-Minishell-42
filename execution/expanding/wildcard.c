/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 20:23:05 by zech-chi          #+#    #+#             */
/*   Updated: 2024/04/02 00:22:30 by zech-chi         ###   ########.fr       */
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

void	ft_list_cwd(t_list **head)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (dir == NULL)
	{
		perror("Error");
		return ;
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
			ft_lstadd_back(head, ft_lstnew(ft_strdup2(entry->d_name)));
		entry = readdir(dir);
	}
	if (closedir(dir) != 0)
		perror("Error");
}

int	ft_get_matching(t_list **head, char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	int				found_match;

	found_match = 0;
	dir = opendir(".");
	if (dir == NULL)
	{
		perror("Error");
		return (0);
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			if (ft_is_match(entry->d_name, pattern))
			{
				ft_lstadd_back(head, ft_lstnew(ft_strdup2(entry->d_name)));
				found_match = 1;
			}
		}
		entry = readdir(dir);
	}
	if (closedir(dir) != 0)
		perror("Error");
	return (found_match);
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
