/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:16:00 by ymomen            #+#    #+#             */
/*   Updated: 2024/04/01 21:40:16 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../header/minishell_parsing.h"
int check_line(char *limiter)
{
    int i;

    i = 0;
    if(limiter && (limiter[0]!= '"'|| limiter[0] != '\'')&& (limiter[ft_strlen(limiter) - 1] != '"' || limiter[ft_strlen(limiter) - 1] != '\''))
        return (1);
    return (0);
}

void	wrt_on_pipe(int *fd, char *limiter, t_tool *tool)
{
	char	*line;

	line = " ";
	while (line)
	{
		line = readline("here_doc> ");
        add_to_grbg(&tool->grbg, line);
		if (!line)
        {
            tool->err = 1;
			write(2 ,"🍪: can get the line from stdin.", 29);
        }
		if (ft_strcmp(line, limiter) == 0)
			return ;
		// if limiter mafihch quotes blama dkhol hna
        if(check_line(limiter) == 1)
		    line = ft_herdoc_expand(line, tool->env, tool->err);
		if (write(*fd, line, ft_strlen(line)) == -1 || write(*fd, "\n", 1) == -1)
        {
			perror(" 🍪: write");
            tool->err = 1;
        }
	}
}
int genratnum(void)
{
    static int i;
    static int j;
    static int k;
    
    i += 3;
    j += 5;
    k += 9;    
    return (i<<16 | j<<8 | k);
}
char *genratname(t_tool *tool)
{
    char    name[30];
    int     cont;
    int     num;
    
    cont = 6;
    ft_strlcpy(name, "/tmp/.", 7);
    while (cont < 30)
    {
        num = genratnum();
        name[cont] = FILENAME[num % 62];
        cont++;
    }
    name[cont] = '\0';
    return (ft_strdup(name, tool));
}
int heredoc(t_tool *tool, char **limiter)
{
    int		fd2;
    char    *name;
    
    name = NULL;
    if(!limiter || !*limiter)
    {
        tool->err = 1;
        return (tool->err) ;
    }
    while(!name || !access(name, F_OK ))
        name = genratname(tool);
    fd2 = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
    *limiter = ft_strdup(name, tool);
    close(fd2);
    return (tool->err);
}
