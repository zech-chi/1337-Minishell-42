/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:56:25 by zech-chi          #+#    #+#             */
/*   Updated: 2024/02/24 15:54:06 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"

void	ft_print_linked_list(t_list *head)
{
	while (head)
	{
		printf("|%s|\n", head->content);
		head = head->next;
	}
}

// open == 0 or ''' or '"'
t_list	*ft_echo_parse(char *prompt)
{
	t_list	*echo_head;
	char	open;
	char	*cur;
	int		i = 0;
	char	str[2];

	open = 0;
	echo_head = NULL;
	cur = NULL;
	while (prompt[i])
	{
		if ((prompt[i] == ' ' || prompt[i] == '"' || prompt[i] == '\'') && open == 0)
		{
			if (cur)
			{
				if (prompt[i] == ' ')
					ft_lstadd_back(&echo_head, ft_lstnew(ft_strjoin(cur, ft_strdup(" "))));
				else
					ft_lstadd_back(&echo_head, ft_lstnew(cur));
			}
			cur = NULL;
			if (prompt[i] == '\'')
			{
				cur = ft_strjoin(cur, ft_strdup("'"));
				open = '\'';
			}
			else if (prompt[i] == '"')
			{
				cur = ft_strjoin(cur, ft_strdup("\""));
				open = '"';
			}
		}
		else if (prompt[i] == '\'')
		{
			cur = ft_strjoin(cur, ft_strdup("'"));
			if (open == 0)
				open = '\'';
			else if (open == '\'')
			{
				if (prompt[i + 1] == ' ')
					ft_lstadd_back(&echo_head, ft_lstnew(ft_strjoin(cur, ft_strdup(" "))));
				else
					ft_lstadd_back(&echo_head, ft_lstnew(cur));
				cur = NULL;
				open = 0;
			}
		}
		else if (prompt[i] == '"')
		{
			cur = ft_strjoin(cur, ft_strdup("\""));
			if (open == 0)
				open = '"';
			else if (open == '"')
			{
				if (prompt[i + 1] == ' ')
					ft_lstadd_back(&echo_head, ft_lstnew(ft_strjoin(cur, " ")));
				else
					ft_lstadd_back(&echo_head, ft_lstnew(cur));
				cur = NULL;
				open = 0;
			}
		}
		else
		{
			str[0] = prompt[i];
			str[1] = 0;
			cur = ft_strjoin(cur, ft_strdup(str));
		}
		i++;
	}
	if (cur)
		ft_lstadd_back(&echo_head, ft_lstnew(cur));
	return (echo_head);
}

int	ft_echo_check_error(t_list *echo_head)
{
	t_list	*last_node;
	char	*s;
	int		len;

	last_node = ft_lstlast(echo_head);
	s = (char *)last_node->content;
	len = ft_strlen(s);
	if (s[0] == '\'' && (len <= 1 || s[len - 1] != s[0]))
		return (1);
	if (s[0] == '"' && (len <= 1 || s[len - 1] != s[0]))
		return (1);
	return (0);
}


void	ft_single_quote(char *s)
{
	int	i;
	int	len;

	len = ft_strlen(s);
	if (len == 2)
		return ;
	i = 1;
	while (i < len - 1)
		printf("%c", s[i++]);
}

int	ft_is_char_in_str(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

void	ft_double_quote(char *s, t_env *env)
{
	int		i;
	int		len;
	char	str[2];
	int		open;
	char	*cur;
	char	*env_s;
	
	open = 0;
	str[1] = 0;
	cur = NULL;
	len = ft_strlen(s);
	if (len == 2)
		return ;
	i = 1;
	while (i < len - 1)
	{
		if (open)
		{
			if (ft_is_char_in_str(SPLITERS, s[i]))
			{
				env_s = ft_env_search(env, cur);
				if (env_s)
					printf("%s", env_s);
				cur = NULL;
				if (s[i] != '$')
				{
					printf("%c", s[i]);
					open = 0;
				}
			}
			else
			{
				str[0] = s[i];
				cur = ft_strjoin(cur, ft_strdup(str));
			}
		}
		else
		{
			if (s[i] == '$')
				open = 1;
			else
				printf("%c", s[i]);
		}
		i++;
	}
	if (cur)
	{
		env_s = ft_env_search(env, cur);
		if (env_s)
		printf("%s", env_s);
	}
}

void	ft_normal_str(char *s, t_env *env)
{
	int i;
	char	str[2];
	int		open;
	char	*cur;
	char	*env_s;

	i = 0;
	open = 0;
	str[1] = 0;
	cur = NULL;
	while (s[i])
	{
		if (open)
		{
			if (ft_is_char_in_str(SPLITERS, s[i]))
			{
				env_s = ft_env_search(env, cur);
				if (env_s)
					printf("%s", env_s);
				cur = NULL;
				if (s[i] != '$')
				{
					printf("%c", s[i]);
					open = 0;
				}
			}
			else
			{
				str[0] = s[i];
				cur = ft_strjoin(cur, ft_strdup(str));
			}
		}
		else
		{
			if (s[i] == '$')
				open = 1;
			else
				printf("%c", s[i]);
		}
		i++;
	}
	if (cur)
	{
		env_s = ft_env_search(env, cur);
		if (env_s)
		printf("%s", env_s);
	}
}

void	ft_echo_print(t_list *head, t_env *env)
{
	int	withnl;
	char *s;

	if (!(head->next))
	{
		printf("\n");
		return ;
	}
	head = head->next;
	withnl = 1 * (!ft_strcmp("-n", head->content));
	if (withnl)
		head = head->next;
	while (head)
	{
		s = (char *)head->content;
		if (s[0] == '\'')
			ft_single_quote(s);
		else if (s[0] == '"')
			ft_double_quote(s, env);
		else 
			ft_normal_str(s, env);
		//if (s[ft_strlen(s) - 1] == ' ')
		//	printf(" ");
		head = head->next;
	}
	if (!withnl)
		printf("\n");
}


int	ft_echo_execute(char *prompt, t_env *env)
{
	char *new_prompt;
	t_list	*echo_head;

	printf("prompt: %s\n", prompt);
	new_prompt = ft_strtrim(prompt, " ");
	printf("new prompt: %s\n", new_prompt);
	if (!ft_strncmp(new_prompt, "echo", 4))
	{
		echo_head = ft_echo_parse(new_prompt);
		ft_print_linked_list(echo_head);
		if (ft_echo_check_error(echo_head) == ERROR)
			printf("error\n");
		else
		{
			printf("good\n");
			printf("-----------------------------\n");
			ft_echo_print(echo_head, env);
		}
	}
	(void)(env);
	return (0);
}
