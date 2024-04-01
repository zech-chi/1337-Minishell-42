/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:25:53 by zech-chi          #+#    #+#             */
/*   Updated: 2024/04/01 15:13:33 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

# include "./minishell_common.h"

typedef struct s_lst
{
	char			*value;
	int				prio;
	int				read;
	int				type;
	struct s_lst	*next;
}	t_lst;

typedef struct s_parse
{
	int	prac;
	int	quot;
	int	err;
}	t_parse;
typedef struct s_garbage
{
	void *ptr;
	struct s_garbage *next;
}	t_garbage;

typedef struct s_tool
{
	int	prac;
	int	quot;
	int	err;
	t_env *env;
	int exit_status;
	t_garbage *grbg;
} t_tool;


/* FUNCTIONS */
void add_to_grbg(t_garbage **head, void *node);
int 	heredoc(int *exit_status, char **limiter);
void 	update_tree(t_tree **root);
t_lst	*pop_last_1(t_lst **stack);
t_lst	*post_new(void *str,int type, int prio, int read);
void	init_type_2(t_lst *node, t_lst *prev);
void	init_type(t_lst **node);
int		is_redarection(int type);
void	redarection_prac_fix(t_lst **head);
void	redarection_perfix_lst(t_lst **head);
void	redarection_join_arg(t_lst **node);
void	ft_putstr_fd(char *s, int fd);
void	print_tree_2d(t_tree *root);
void	update_lst(t_lst **node);
void	is_operateur_tree(t_tree **node);
void	is_quot_parc_open(t_parse *par_line, char command, int qorp);
void	trime(t_lst *head);
char	*ft_monstrdup(const char *s1, size_t size, t_garbage **grbg);
void	is_operateur(t_lst **node);
int		is_delimter(char c);

/* LIBFT */
char	*ft_strjoin(char const *s1, char const *s2, t_tool *tool);
int		ft_strcmp(char *s1, char *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strtrim(const char *s1, const char *set, t_tool *tool);
char	*ft_strdup(const char *s1, t_garbage **grbg);

	/*tree*/
t_tree	*parsing(char *line, t_tool *tool);
t_tree	*postfix_tree(t_lst *postfix);
t_tree	*new_node(char *value, int prio, int type, int read);
t_tree	*insertIntoBST(t_tree *root, char *value);
t_lst	*from_infix_to_Postfix(t_lst *head, t_tool *tool);

/* lst*/
t_lst	*lst_pop(t_lst **lst);
void	lst_add_front(t_lst **lst, t_lst *new);
void	lst_clear(t_lst *head);
t_lst	*lastone(t_lst *head);
void	lst_add_back(t_lst **head, t_lst *node);
t_lst	*lst_new(void *str, t_tool *tool);
t_lst	*tokens_lst(char *command, t_tool *tool);
void	*pop_last(t_lst **stack);
int		size_lst(t_lst **head);

#endif