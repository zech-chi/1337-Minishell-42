/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execution.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:07:18 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/24 21:44:46 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXECUTION_H
# define MINISHELL_EXECUTION_H

# include "./minishell_common.h"

# define SUCCESS 0
# define FAILED 1

//colors
# define RED_COLOR   "\x1b[31m"
# define GREEN_COLOR "\x1b[32m"
# define RESET_COLOR "\x1b[0m"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);

// functions:

/* libft tools */
char	**ft_split2(char const *s, char c);
int		ft_strcmp2(char *s1, char *s2);
char	*ft_strdup2(const char *s1);
char	*ft_strjoin2(char *s1, char *s2);
size_t	ft_strlen2(const char *s);
int		ft_strncmp2(const char *s1, const char *s2, size_t n);
char	*ft_strtrim2(char const *s1, char const *set);
char	*ft_itoa2(int n);
void	ft_putstr_fd2(char *s, int fd);
void	ft_put_error(char *s);
int		ft_isspace(char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
/* builtins */

// echo
void	ft_echo(char **cmd_2d);


// env
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	int				visible;
}	t_env;

# define SPACE ' '
# define EQUAL '='

t_env	*ft_env_create(char **ev);
t_env	*ft_env_duplicate(t_env *env);
int		ft_env_add(t_env **env, char *key, char *value, int visible);
int		ft_env_update(t_env **env, char *key, char *newval, int append_mod);
void	ft_env_delete(t_env **env, char *key);
char	*ft_env_search(t_env *env, char *key);
void	ft_env_print(t_env *env);
void	ft_env_clear(t_env **env);
int		ft_env_size(t_env *env);
char	**ft_env_create_2d(t_env *env);

// cd
int	ft_cd(char **splited_prompt, t_env **env);

// export
void	ft_export(t_env **env, char **cmd_2d, int *exit_status);

// pwd
void	ft_pwd_print(void);

// unset
void	ft_unset(t_env **env, char **cmd_2d, int *exit_status);

// exit
void	ft_exit(char **cmd_2d, int *exit_status);

// env
void	ft_env(t_env *env, char **cmd_2d, int *exit_status);

// expand.c

# define DELIMITERS "$%!^~,. +=&?#@*[]()-/\"'"

typedef struct s_expand
{
	t_list	*head;
	int		quote;
	int		noting_before_quote;
	int		noting_before_env_var;
	char	*buff_exp;
	char	*buff_env;
	char	*buff_star;
	char	**cmd_2d;
	int		i;
	int		found_star;
	int		found_another_char;
}	t_expand;

char	*ft_char_to_str(char c);
int		ft_is_delimiter(char c);
void	ft_print_lst(t_list *node); // to remove
char	**ft_lst_to_2d_char(t_list *head);
void	ft_list_cwd(t_list **head);
void	ft_exp_init(t_expand *exp);
char	**ft_expand(char *prompt, t_env *env, int exit_status);

// execute.c
void	ft_execute_search_in_path(char **cmd_2d, t_env *env);
void	ft_execute_cmd(char *cmd, t_env **env, int *exit_status);
void	ft_execute(t_tree *root, t_env **env, int *exit_status);

// pipe.c
void	ft_execute_pipe(t_tree *root, t_env **env, int *exit_status);

// execute_builtins.c
int		ft_execute_builtins(char **cmd_2d, t_env **env, int *exit_status);

// execute_redirection_out.c
void	ft_execute_redirection_out(t_tree *root, t_env **env, int *exit_status);

#endif