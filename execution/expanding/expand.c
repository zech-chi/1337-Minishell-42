/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:36:52 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/16 00:53:50 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

typedef struct s_expand {
	t_list	*head;
	int		open;
	char	*buff_exp;
	char	*buff_env;
	char	**cmd_2d;
	int		i;
}	t_expand;

// "$;!?*%#"
int	ft_is_char_in_str(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_char_to_str(char c)
{
	char	str[2];

	str[0] = c;
	str[1] = 0;
	return (ft_strdup2(str));
}

/// to remove
void	ft_print_lst(t_list *node)
{
	while (node)
	{
		printf("{%s}\n", node->content);
		node = node->next;
	}
}

char	**ft_lst_to_2d_char(t_list *head)
{
	char	**char_2d;
	int		r;

	char_2d = (char **)malloc(sizeof(char *) * (ft_lstsize(head) + 1));
	if (!char_2d)
		return (NULL);
	r = 0;
	while (head)
	{
		char_2d[r] = head->content;
		head = head->next;
		r++;
	}
	char_2d[r] = NULL;
	return (char_2d);
}

char	*ft_list_cwd(t_env *env)
{
	char	*buff;
	DIR		*dir;
	struct	dirent *entry;

	dir = opendir(ft_env_search(env, "PWD"));
	buff = NULL;
	if (dir == NULL)
	{
		perror("Error");
		return (NULL);
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			if (buff)
				buff = ft_strjoin2(buff, ft_strjoin2(" ", entry->d_name));
			else
				buff = ft_strdup2(entry->d_name);
		}
	}
	if (closedir(dir) != 0)
		perror("Error");
	return (buff);
}

void	ft_wild_card(t_list **head, t_env *env)
{
	t_list	*tmp;
	int		i;

	tmp = *head;
	while (tmp)
	{
		i = 0;
		while (((char *)tmp->content)[i] && ((char *)tmp->content)[i] == '*')
			i++;
		if (!((char *)tmp->content)[i])
			tmp->content = ft_list_cwd(env);
		tmp = tmp->next;
	}
}

static void	ft_exp_init(t_expand *exp)
{
	exp->buff_exp = NULL;
	exp->buff_env = NULL;
	exp->cmd_2d = NULL;
	exp->head = NULL;
	exp->i = -1;
	exp->open = 0;
}

static void	ft_expand_help1(t_expand *exp)
{
	if (exp->buff_exp)
	{
		ft_lstadd_back(&(exp->head), ft_lstnew(exp->buff_exp));
		exp->buff_exp = NULL;
	}
}

static void	ft_expand_help2(t_expand *exp, char c)
{
	if (exp->open == 0)
		exp->open = c;
	else if (exp->open == c)
		exp->open = 0;
	else
		exp->buff_exp = ft_strjoin2(exp->buff_exp, ft_char_to_str(c));
}

static void	ft_expand_help3(t_expand *exp, t_env *env, char *cmd, int exit_status)
{
	while (cmd[exp->i] && cmd[exp->i] == '$')
	{
		exp->buff_env = ft_char_to_str(cmd[(exp->i)++]);
		while (cmd[exp->i] && !ft_is_char_in_str(cmd[exp->i], "$, +=?#@*\"'"))
			exp->buff_env = ft_strjoin2(exp->buff_env, ft_char_to_str(cmd[(exp->i)++]));
		exp->buff_exp = ft_strjoin2(exp->buff_exp, ft_env_search(env, exp->buff_env + 1));
		if (cmd[exp->i] == '?' && ft_strlen2(exp->buff_env) == 1)
			exp->buff_exp = ft_strjoin2(exp->buff_exp, ft_itoa2(exit_status));
		else if (cmd[exp->i] == ' ')
			ft_expand_help1(exp);
		else if (cmd[exp->i] == '"' || cmd[exp->i] == '\'')
			ft_expand_help2(exp, cmd[exp->i]);
		else if (cmd[exp->i] && cmd[exp->i] != '$' && cmd[exp->i] != ' ')
			exp->buff_exp = ft_strjoin2(exp->buff_exp, ft_char_to_str(cmd[exp->i]));
		else if (ft_strlen2(exp->buff_env) == 1 && !cmd[exp->i])
			exp->buff_exp = ft_strjoin2(exp->buff_exp, exp->buff_env);
		exp->buff_env = NULL;
	}
}

char	**ft_expand(char *cmd, t_env *env, int exit_status)
{
	t_expand	exp;

	ft_exp_init(&exp);
	while (cmd[++(exp.i)])
	{
		if (cmd[exp.i] == ' ' && exp.open == 0)
			ft_expand_help1(&exp);
		else if (cmd[exp.i] == '"' || cmd[exp.i] == '\'')
			ft_expand_help2(&exp, cmd[exp.i]);
		else if (cmd[exp.i] == '$' && exp.open != '\'')
			ft_expand_help3(&exp, env, cmd, exit_status);
		else
			exp.buff_exp = ft_strjoin2(exp.buff_exp, ft_char_to_str(cmd[exp.i]));
		if (!cmd[exp.i])
			break;
	}
	if (exp.buff_exp)
		ft_expand_help1(&exp);
	//ft_print_lst(exp.head);
	return (ft_lst_to_2d_char(exp.head));
}
