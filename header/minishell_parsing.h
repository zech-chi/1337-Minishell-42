/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:55:53 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/15 18:20:04 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_V1_H
# define MINISHELL_V1_H

#include "./minishell_common.h"

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

int err;

t_lst *from_infix_to_Postfix(t_lst *head);
/* FUNCTIONS */
t_tree *parsing (char * line);
void print_tree_2d(t_tree *root);
void fix_ls(t_lst **node);
void	update_lst(t_lst **node);
char	*ft_strjoin(char const *s1, char const *s2);
void	is_operateur_tree(t_tree **node);
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
void	lst_add_front(t_lst **lst, t_lst *new);
void lst_clear(t_lst *head);
t_lst *lastone(t_lst *head);
void lst_add_back(t_lst **head, t_lst *node);
t_lst *lst_new(void *str);
t_lst *tokens_lst(char *command);
void *pop_last(t_lst **stack);
int size_lst(t_lst **head);
#endif