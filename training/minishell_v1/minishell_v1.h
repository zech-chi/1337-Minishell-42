/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_v1.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:13:08 by ymomen            #+#    #+#             */
/*   Updated: 2024/02/25 23:42:25 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_V1_H
# define MINISHELL_V1_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
#include <readline/readline.h>

/* (=6 )=7 |=3 "=9 '=5 <=1 >=2 ;=8 &=4 >>=10 <<=11 &&=12 ||=13 */
# define REDIRECTION 1
# define LESS_THAN 2
# define PIPE 3
 #define SINGL_AND 4
# define AND 5
# define OR 6
# define SINGLE_QUAT 7
# define DOUBLE_QUAT 8
# define APEND_REDIRECTION 9
#define HERE_DOC 10
# define CLOSE_PARENTH 11
# define OPEN_PARENTH 12

typedef struct s_tree
{
	int			indx;
	struct s_tree	*right;
	struct s_tree	*left;
}	t_tree;

typedef struct s_lst
{
	char			*value;
	struct s_lst	*next;
}t_lst;


/* FUNCTIONS */
char **lst_to_arr(t_lst *head);
void lst_clear(t_lst *head);
int size_lst(t_lst *head);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strtrim(const char *s1, const char *set);
void lst_add_back(t_lst **head, t_lst *node);
t_lst *lst_new(char *str);
t_lst *tokens_lst(char *command);
t_tree	*insertIntoBST(t_tree* root, int indx);
t_tree	*tree_new(int value);
char	*ft_strdup(const char *s1);
// char	*ft_strchr_v2(const char *s, int c, char *del);
// char	*ft_strtok(char *str);
// t_tree	*creat_tree(char *str);
// void	ft_bzero(void *s, size_t n);

#endif