/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_v2.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 21:15:30 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/02 15:01:16 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_V2_H
# define MINISHELL_V2_H

# include <sys/param.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <errno.h>
# include <fcntl.h>

#define SUCCESS 0
#define FAILED 1

/* tree stafff */
typedef struct s_node {
	char			*data;
	int				index;
	int				type;
	int				fd[2];
	struct s_node	*left;
	struct s_node	*right;
} t_node;

//types:
#define CMD 0                    // example: ls
#define PIPE 1                   // |
#define AND 2                    // &&
#define OR 3                     // ||
#define REDIRECT_OUTPUT 4        // >
#define REDIRECT_OUTPUT_APPEND 5 // >>
#define REDIRECT_INPUT 6         // <
#define HEREDOC 7                // <<
// functions:
t_node	*ft_create_node(char *data, int index, int	type);
t_node	*ft_insert_node(t_node *root, char *data, int index, int type);
void	ft_inorder_traversal(t_node *root);
t_node	*ft_build_tree(void);

/* libft tools */
char	**ft_split(char const *s, char c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strtrim(char const *s1, char const *set);


/* builtins */

// env
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

#define SPACE ' '
#define EQUAL '='

t_env	*ft_env_create(char **ev);
int		ft_env_add(t_env **env, char *key, char *value);
int		ft_env_update(t_env **env, char *key, char *newval);
void	ft_env_delete(t_env **env, char *key);
char	*ft_env_search(t_env *env, char *key);
void	ft_env_print(t_env *env);
void	ft_env_clear(t_env **env);
int		ft_env_size(t_env *env);
char	**ft_env_create_2d(t_env *env);
#endif