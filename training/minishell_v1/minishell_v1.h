/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_v1.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:13:08 by ymomen            #+#    #+#             */
/*   Updated: 2024/02/22 22:00:48 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_V1_H
# define MINISHELL_V1_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

/* (=1; )=2; |=3; "=4; '=5; <=6; >=7; &&=8; ||=9;*/
# define OPEN_PARENTH 1
# define CLOSE_PARENTH 2
# define PIPE 3
# define DOUBLE_QUAT4
# define SINGLE_QUAT 5
# define LESS_THAN 6
# define GTRATER_THAN 7
# define AND 8
# define OR 9

typedef struct s_tree
{
	char			*value;
	struct s_tree	*right;
	struct s_tree	*left;
}	t_tree;

/* FUNCTIONS */
t_tree	*creat_tree(char *str);
void	ft_bzero(void *s, size_t n);
t_tree	*new_node(char *str);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c, char *del);
char	*ft_strtok(char *str, char	*delim, char *del);

#endif