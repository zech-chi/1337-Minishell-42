/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_v1.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:53:17 by zech-chi          #+#    #+#             */
/*   Updated: 2024/02/23 18:54:55 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_V1_H
# define MINISHELL_V1_H

#include <sys/param.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <errno.h>



typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);


typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// exit status
#define SUCCESS 0
#define FAILED 1


#define SPACE ' '
#define EQUAL '='

// echo.c
int	ft_echo_execute(char *prompt, t_env *env);

// strcmp
int	ft_strcmp(char *s1, char *s2);

// strjoin.c file
char	*ft_strjoin(char *s1, char *s2);

// strlen.c file
size_t	ft_strlen(const char *s);

// strdup.c file
char	*ft_strdup(const char *s1);

// split.c
char	**ft_split(char const *s, char c);

// strncmp
int	ft_strncmp(const char *s1, const char *s2, size_t n);

// strtrim
char	*ft_strtrim(char const *s1, char const *set);

// env.c file
int		ft_env_add(t_env **env, char *key, char *value);
t_env	*ft_env_create(char **ev);
void	ft_env_print(t_env *env);
char	*ft_env_search(t_env *env, char *key);
void	ft_env_clear(t_env **env);
char	**ft_env_create_2d(t_env *env);
int		ft_env_size(t_env *env);
int		ft_env_update(t_env **env, char *key, char *newval);
void	ft_env_delete(t_env **env, char *key);






#endif