/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:16:00 by ymomen            #+#    #+#             */
/*   Updated: 2024/04/16 11:02:08 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

static	int	check_line(char **limiter, t_tool *tool)
{
	char	*lim;

	if (!limiter || !*limiter)
		return (0);
	lim = *limiter;
	if (lim && (lim[0] != '"' && lim[0] != '\'')
		&& (lim[ft_strlen(lim) - 1] != '"'
			&& lim[ft_strlen(lim) - 1] != '\''))
		return (0);
	if (*limiter && (*limiter[0] == '\''
			&& *limiter[ft_strlen(*limiter) - 1] == '\''))
		*limiter = ft_strtrim(*limiter, "'", tool);
	else
		*limiter = ft_strtrim(*limiter, "\"", tool);
	return (1);
}

//int check_line(char *limiter)
//{
//    //int i;

//    //i = 0;
//    if(limiter && (limiter[0]!= '"'|| limiter[0] != '\'')&& (limiter[ft_strlen(limiter) - 1] != '"' || limiter[ft_strlen(limiter) - 1] != '\''))
//        return (1);
//    return (0);
//}

static void	wrt_on_file(int *fd, char *limiter, t_tool *tool)
{
	char	*line;
	int		i;

	line = " ";
	i = 0;
	if (!check_line(&limiter, tool))
		i = 1;
	while (line)
	{
		line = readline("here_doc> ");
		if (!line)
			return ;
		add_to_grbg(&(tool->grbg), line);
		if (i && limiter && limiter[0] != '$')
		{
			line = ft_herdoc_expand(line, tool->env, tool->err);
			add_to_grbg(&(tool->grbg), line);
		}
		if (check_here_doc(line, fd, limiter, tool) == 0)
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
