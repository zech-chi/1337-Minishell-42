/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_common.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:27:47 by zech-chi          #+#    #+#             */
/*   Updated: 2024/04/17 16:25:24 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_COMMON_H
# define MINISHELL_COMMON_H

# include <sys/param.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>
# include <limits.h>
# include <sys/wait.h>

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
# define OPERAND 0
# define OUTFILE -2
# define INFILE -3
# define LIMITER -4
# define OUTFILE_APPAND -5

# define L_TO_R 3
# define R_TO_L 2

enum e_peroirty
{
	open_par = 6 ,
	close_par = 6,
	and = 5,
	or = 5,
	pip = 3,
	redir = 1,
	appand = 1,
	here_doc = 1,
	input = 1
};

typedef struct s_tree
{
	char			*value;
	int				prio;
	int				read;
	int				type;
	struct s_tree	*right;
	struct s_tree	*left;
}	t_tree;

/************************* env struct *************************/
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	int				visible;
}	t_env;

/************************* her_doc struct *************************/
typedef struct s_expand_herdoc
{
	char	*buff_exp;
	char	*buff_env;
	int		exit_status;
	t_env	*env;
	int		i;
}	t_expand_herdoc;

char	*ft_herdoc_expand(char *str, t_env *env, int exit_status);
char	**ft_split2(char const *s, char c);
char	*ft_strjoin2(char *s1, char *s2);
char	*ft_char_to_str(char c);
void	ft_handle_signals(int sig);
#endif