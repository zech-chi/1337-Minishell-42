/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:16:00 by ymomen            #+#    #+#             */
/*   Updated: 2024/04/01 01:02:50 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_parsing.h"

void	wrt_on_pipe(int *fd, char *limiter, int *exit_status)
{
	char	*line;

	line = " ";
	while (line)
	{
		line = readline("here_doc> ");
		if (!line)
        {
            *exit_status = 1;
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
            *exit_status = 1;
        }
		free(line);
	}
}

int heredoc(int *exit_status, char **limiter)
{
    int		fd2;
    
    if(!limiter || !*limiter)
    {
        *exit_status = 1;
        return (*exit_status) ;
    }
    
    fd2 = open("/tmp/here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd2 == -1)
    {
        perror("open");
        *exit_status = 1;
    }
	wrt_on_pipe(&fd2, *limiter, exit_status);
	if (close(fd2) == -1)
		{
        perror("open");
        *exit_status = 1;
        }
    free (*limiter);
    *limiter = ft_strdup("/tmp/here_doc");
    return (*exit_status);
}
