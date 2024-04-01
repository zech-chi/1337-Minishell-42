/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:16:00 by ymomen            #+#    #+#             */
/*   Updated: 2024/04/01 14:30:58 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

void	wrt_on_pipe(int *fd, char *limiter, t_tool *tool)
{
	char	*line;

	line = " ";
	while (line)
	{
		line = readline("here_doc> ");
		if (!line)
        {
            tool->err = 1;
			write(2 ,"🍪: can get the line from stdin.", 29);
        }
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			return ;
		}
		if (write(*fd, line, ft_strlen(line)) == -1 || write(*fd, "\n", 1) == -1)
        {
			perror(" 🍪: write");
            tool->err = 1;
        }
		free(line);
	}
}

int heredoc(t_tool *tool, char **limiter)
{
    int		fd2;
    
    if(!limiter || !*limiter)
    {
        tool->err = 1;
        return (tool->err) ;
    }
    
    fd2 = open("/tmp/here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd2 == -1)
    {
        perror("open");
        tool->err = 1;
    }
	wrt_on_pipe(&fd2, *limiter, tool);
	if (close(fd2) == -1)
		{
        perror("open");
        tool->err = 1;
        }
    free (*limiter);
    *limiter = ft_strdup("/tmp/here_doc");
    return (tool->err);
}
