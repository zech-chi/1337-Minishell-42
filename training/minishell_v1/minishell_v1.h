/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_v1.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:13:08 by ymomen            #+#    #+#             */
/*   Updated: 2024/03/07 18:42:36 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_V1_H
# define MINISHELL_V1_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>

enum e_peroirty { open_par = 6 , close_par = 6, and = 5, or = 5, pip = 3, redir = 1, appand = 1, here_doc = 2, input = 1};
/* (=6 )=7 |=3 "=9 '=5 <=1 >=2 ;=8 &=4 >>=10 <<=11 &&=12 ||=13 */
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

#define OPERAND 0;
typedef struct s_tree
{
	char			*value;
	
	struct s_tree	*right;
	struct s_tree	*left;
}	t_tree;

typedef struct s_lst
{
	char			*value;
	int				prio;
	int				read;
	int				type;
	struct s_lst	*next;
}t_lst;
typedef struct s_parse
{
	int	prac;
	int	quot;
}t_parse;

void print2D(t_tree * root);

t_lst *from_infix_to_Postfix(t_lst *head);
/* FUNCTIONS */
void	is_quot_parc_open(t_parse *par_line, char command, int qorp);
int	ft_strcmp(char *s1, char *s2);
void	trime(t_lst *head);
void	init_type(t_lst *prev, t_lst *node);
char	*ft_monstrdup(const char *s1, size_t size);
void is_operateur(t_lst **node);
int check_arr(char *arr);
int is_delimter(char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_strdup(const char *s1);

	/*tree*/
t_tree *postfix_tree(t_lst *postfix);
t_tree	*new_node(char *value);
t_tree	*insertIntoBST(t_tree* root, char *value);


/* lst*/
t_lst *lst_pop(t_lst **lst);
void	lst_push(t_lst **lst, t_lst *new);
void lst_clear(t_lst *head);
t_lst *lastone(t_lst *head);
void lst_add_back(t_lst **head, t_lst *node);
t_lst *lst_new(void *str);
t_lst *tokens_lst(char *command);
void *pop_last(t_lst **stack);
int size_lst(t_lst **head);
#endif
// void is_parc_open(int *parc, char command, int pass);
// char **lst_to_arr(t_lst *head);