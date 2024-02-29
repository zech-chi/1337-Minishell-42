/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_v1.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:13:08 by ymomen            #+#    #+#             */
/*   Updated: 2024/02/29 23:32:01 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_V1_H
# define MINISHELL_V1_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
#include <readline/readline.h>

enum e_peroirty{open_par = 6 , close_par = 6, and = 4, or = 4, pip = 3, redir = 1, appand = 1, here_doc = 2, input = 1};
/* (=6 )=7 |=3 "=9 '=5 <=1 >=2 ;=8 &=4 >>=10 <<=11 &&=12 ||=13 */
# define REDIRECTION 1
# define INPUT 2
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
#define COMMAND 0

# define L_TO_R 3
# define R_TO_L 2
#define L_R_R_L 1
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
typedef struct s_stack
{
	void			*value;
	struct s_stack	*next;
}t_stack;


/* FUNCTIONS */
void print2D(t_tree * root);

void is_parc_open(int *parc, char command, int pass);
t_lst *lastone(t_lst *head);
void is_operateur(t_lst **node);
char check_arr(char *arr);
void *pop_last(t_lst **stack);
void from_infix_to_Postfix(t_lst *head, t_lst **postfix);
int is_delimter(char c);
char **lst_to_arr(t_lst *head);
void lst_clear(t_lst *head);
int size_lst(t_lst **head);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strtrim(const char *s1, const char *set);
void lst_add_back(t_lst **head, t_lst *node);
t_lst *lst_new(char *str);
t_lst *tokens_lst(char *command);
char	*ft_strdup(const char *s1);
// t_tree	*tree_new(int value);
// char	*ft_strchr_v2(const char *s, int c, char *del);
// char	*ft_strtok(char *str);
// t_tree	*creat_tree(char *str);
// void	ft_bzero(void *s, size_t n);

	/*tree*/
t_tree *postfix_tree(t_lst *postfix);
t_tree	*new_node(char *value);
t_tree	*insertIntoBST(t_tree* root, char *value);
	/*stack*/
t_stack *lastonstack(t_stack *head);
void	ft_stackadd_front(t_stack **stack, t_stack *new);
void *pop_stack(t_stack **stack);
void stack_clear(t_stack *head);
int size_stack(t_stack **head);
void stack_add_back(t_stack **head, t_stack *node);
t_stack *stack_new(void *str);
#endif