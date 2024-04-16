/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:16:00 by ymomen            #+#    #+#             */
/*   Updated: 2024/04/16 17:05:17 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

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
			to_expand = 0;
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

static void	wrt_on_file(int *fd, char *limiter, t_tool *tool)
{
	char	*line;
	int		i;

	line = " ";
	i = 1;
	limiter = ft_update_delimiter(limiter, &i);
	add_to_grbg(&(tool->grbg), limiter);
	while (line)
	{
		line = readline("here_doc> ");
		if (!line)
			return ;
		add_to_grbg(&(tool->grbg), line);
		if (line && ft_strcmp(line, limiter) == 0)
			return ;
		if (i && limiter)
		{
			line = ft_herdoc_expand(line, tool->env, tool->err);
			add_to_grbg(&(tool->grbg), line);
		}
		if (check_here_doc(line, fd, tool) == 0)
			return ;
		line = " ";
	}
}

static int	genratnum(void)
{
	static int	i;
	static int	j;
	static int	k;

	i += 3;
	j += 5;
	k += 9;
	return (i << 16 | j << 8 | k);
}

static char	*genratname(t_tool *tool)
{
	char	*name;
	int		cont;
	int		num;

	cont = 6;
	name = (char *) malloc(31);
	if (!name)
		return (perror("🍪 : malloc"), tool->err = 1, NULL);
	add_to_grbg(&(tool->grbg), name);
	ft_strlcpy(name, "/tmp/.", 30);
	while (cont < 30)
	{
		num = genratnum();
		name[cont] = FILENAME[num % 60];
		cont++;
	}
	name[cont] = '\0';
	return (name);
}

int	heredoc(t_tool *tool, char **limiter)
{
	int		fd2;
	char	*name;

	name = NULL;
	if (!limiter)
		return (tool->err = 1, 1);
	while (!name || !access(name, F_OK))
		name = genratname(tool);
	fd2 = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd2 == -1)
		return (perror("open"), tool->err = 1, 1);
	wrt_on_file(&fd2, *limiter, tool);
	if (close(fd2) == -1)
		return (perror("open"), tool->err = 1, 1);
	*limiter = ft_strdup(name, tool);
	return (0);
}
