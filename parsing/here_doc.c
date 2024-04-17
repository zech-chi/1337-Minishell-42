/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:16:00 by ymomen            #+#    #+#             */
/*   Updated: 2024/04/17 16:53:07 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

int	open_file(char *name, t_tool *tool)
{
	int	fd;

	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("open"), tool->err = 1, 1);
	return (fd);
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
	fd2 = open_file(name, tool);
	if (wrt_on_file(&fd2, *limiter, tool) == 1)
		fd2 = open_file(name, tool);
	if (close(fd2) == -1)
		return (perror("open"), tool->err = 1, 1);
	*limiter = ft_strdup(name, tool);
	signal(SIGINT, ft_handle_signals);
	signal(SIGQUIT, ft_handle_signals);
	return (0);
}
