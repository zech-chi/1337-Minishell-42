/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:43:16 by zech-chi          #+#    #+#             */
/*   Updated: 2024/04/16 17:49:39 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d;
	size_t	s;
	size_t	dst_len;
	size_t	src_len;

	if (dst == NULL && dstsize == 0)
		return (0);
	dst_len = ft_strlen2(dst);
	src_len = ft_strlen2(src);
	if (dst_len >= dstsize)
		return (src_len + dstsize);
	d = dst_len;
	s = 0;
	while (src[s] && d < dstsize - 1)
	{
		dst[d] = src[s];
		d++;
		s++;
	}
	dst[d] = '\0';
	return (dst_len + src_len);
}

char	*ft_get_cwd(char *tojoin, int i)
{
	char		cwd[MAXPATHLEN];
	static char	save_cwd[MAXPATHLEN];

	if (getcwd(cwd, MAXPATHLEN) != NULL)
		ft_strlcpy2(save_cwd, cwd, MAXPATHLEN);
	else if (i == 1)
	{
		ft_strlcat(save_cwd, "/", MAXPATHLEN);
		ft_strlcat(save_cwd, tojoin, MAXPATHLEN);
	}
	return (ft_strdup2(save_cwd)); // must free
}

void	ft_pwd_print(void)
{
	char	*cwd;

	cwd = ft_get_cwd(NULL, 0);
	printf("%s\n", cwd);
	free(cwd);
}
