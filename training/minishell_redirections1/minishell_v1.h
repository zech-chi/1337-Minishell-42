/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_v1.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:33:21 by zech-chi          #+#    #+#             */
/*   Updated: 2024/02/25 16:25:19 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_V1_H
# define MINISHELL_V1_H

#include <sys/param.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <errno.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// exit status
#define SUCCESS 0
#define FAILED 1

// split by
#define SPACE ' '
#define EQUAL '='

// builtins
#define ENV "env"
#define EXIT "exit"
#define PWD "pwd"
#define CD "cd"
#define EXPORT "export"
#define UNSET "unset"
/*
	*functions prototypes*
*/



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

// strcmp.c file
int	ft_strcmp(char *s1, char *s2);

// strjoin.c file
char	*ft_strjoin(char *s1, char *s2);

// strlen.c file
size_t	ft_strlen(const char *s);

// strdup.c file
char	*ft_strdup(const char *s1);

// pwd.c
void	ft_pwd_print();

char	*ft_strtrim(char const *s1, char const *set);

int	ft_export(t_env **env, char **splited_prompt);

int	ft_cd(char **splited_prompt, t_env **env);

int ft_unset(t_env **env, char **splited_prompt);


char	**ft_split(char const *s, char c);
//void	ft_execute(char *prompt, t_env **env);
void	ft_execute(char *prompt, t_env **env, int redirections, char *file_path);


#endif