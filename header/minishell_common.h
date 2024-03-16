/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_common.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:12:58 by zech-chi          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/16 07:44:24 by ymomen           ###   ########.fr       */
=======
/*   Updated: 2024/03/16 17:07:43 by zech-chi         ###   ########.fr       */
>>>>>>> v3
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_COMMON_H
# define MINISHELL_COMMON_H

# include <sys/param.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>

<<<<<<< HEAD
enum e_peroirty { open_par = 6 , close_par = 6, and = 5, or = 5, pip = 3, redir = 1, appand = 1, here_doc = 1, input = 1};
=======
enum e_peroirty
{
	open_par = 6,
	close_par = 6,
	and = 5,
	or = 5,
	pip = 3,
	redir = 1,
	appand = 1,
	here_doc = 2,
	input = 1
};

>>>>>>> v3
# define REDIRECTION 1
# define INPUT 2
# define PIPE 3
# define SINGL_AND 4
# define AND 5
# define OR 6
# define SINGLE_QUAT 7
# define DOUBLE_QUAT 8
# define APPEND_REDIRECTION 9
# define HERE_DOC 10
# define CLOSE_PARENTH 11
# define OPEN_PARENTH 12
# define OUTFILE -2
# define INFILE -3
# define LIMITER -4
# define OUTFILE_APPAND -5

# define L_TO_R 3
# define R_TO_L 2
# define L_R_R_L 1
# define OPERAND 0

typedef struct s_tree
{
	char			*value;
	int				prio;
	int				read;
	int				type;
	struct s_tree	*right;
	struct s_tree	*left;
}	t_tree;

#endif