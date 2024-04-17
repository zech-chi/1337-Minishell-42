/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:16:46 by ymomen            #+#    #+#             */
/*   Updated: 2024/04/17 18:23:17 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

void	ft_handler(int sig)
{
	if (sig == SIGINT)
		close(0);
}

int	line_check(char **line, t_tool *tool, int i, char *limiter)

{
	if (!line || !*line)
		return (0);
	add_to_grbg(&(tool->grbg), *line);
	if (*line && ft_strcmp(*line, limiter) == 0)
		return (0);
	if (i && limiter)
	{
		*line = ft_herdoc_expand(*line, tool->env, tool->err);
		add_to_grbg(&(tool->grbg), *line);
	}
	return (1);
}

static char	*ft_update_delimiter(char *delimiter, int *to_expand)
{
	char	*new_delimiter;
	char	quote;
	int		i;

	new_delimiter = NULL;
	quote = 0;
	i = -1;
	while (delimiter && delimiter[++i])
	{
		if (delimiter[i] == '\'' || delimiter[i] == '"')
		{
			*to_expand = 0;
			if (quote == 0)
				quote = delimiter[i];
			else if (quote == delimiter[i])
				quote = 0;
			else
				new_delimiter = ft_strjoin2(new_delimiter, \
				ft_char_to_str(delimiter[i]));
		}
		else
			new_delimiter = ft_strjoin2(new_delimiter, \
			ft_char_to_str(delimiter[i]));
	}
	return (new_delimiter);
}

int	wrt_on_file(int *fd, char *limiter, t_tool *tool)
{
	char	*line;
	int		i;

	line = " ";
	i = 1;
	limiter = ft_update_delimiter(limiter, &i);
	add_to_grbg(&(tool->grbg), limiter);
	signal(SIGINT, ft_handler);
	while (line)
	{
		line = readline("here_doc> ");
		if (!ttyname(0))
		{
			open(ttyname(2), O_RDWR);
			close(*fd);
			return (1);
		}
		if (!line_check(&line, tool, i, limiter))
			return (0);
		if (check_here_doc(line, fd, tool) == 0)
			return (1);
		line = " ";
	}
	return (1);
}
