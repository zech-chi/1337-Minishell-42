/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:39:39 by zech-chi          #+#    #+#             */
/*   Updated: 2024/03/26 21:44:38 by zech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell_execution.h"

static int	ft_is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && !str[i + 1] && i != 0)
			return (1);
		if ('0' <= str[i] && str[i] <= '9' && i == 0)
			return (-1);
		if (
			!(
			('0' <= str[i] && str[i] <= '9')
			|| ('a' <= str[i] && str[i] <= 'z')
			|| ('A' <= str[i] && str[i] <= 'Z')
			|| str[i] == '_'
			)
		)
			return (-1);
		i++;
	}
	return (0);
}

static void	ft_swap(t_env	*node1, t_env	*node2)
{
	char	*tmp_value;
	char	*tmp_key;

	tmp_key = node1->key;
	tmp_value = node1->value;
	node1->key = node2->key;
	node2->key = tmp_key;
	node1->value = node2->value;
	node2->value = tmp_value;
}

static void	ft_print_sorted_env(t_env **env_dup)
{
	t_env	*left;
	t_env	*right;
	t_env	*cur;

	left = *env_dup;
	while (left && left->next)
	{
		right = left->next;
		while (right)
		{
			if (ft_strcmp2(left->key, right->key) > 0)
				ft_swap(left, right);
			right = right->next;
		}
		left = left->next;
	}
	cur = *env_dup;
	while (cur)
	{
		printf("declare -x %s=\"%s\"\n", cur->key, cur->value);
		cur = cur->next;
	}
	ft_env_clear(env_dup);
}

char	*ft_get_slice(char *str, int *right, char stop)
{
	char	*slice;
	int		left;
	int		i;

	if (!str)
		return (NULL);
	left = *right;
	while (str[*right] && str[*right] != stop)
		(*right)++;
	slice = (char *)malloc(sizeof(char) * (*right - left) + 1);
	i = 0;
	while (left < *right)
		slice[i++] = str[left++];
	slice[i] = '\0';
	return (slice);
}

void	ft_export_help(char *str, t_env **env, int *exit_status)
{
	char	*slice1;
	char	*slice2;
	int		right;
	int		found_equal;
	int		append_mod;

	found_equal = 0;
	right = 0;
	slice1 = ft_get_slice(str, &right, '=');
	if (str[right] == '=')
	{
		found_equal = 1;
		right++;
	}
	slice2 = ft_get_slice(str, &right, '\0');
	append_mod = ft_is_valid_identifier(slice1);
	if (append_mod == -1)
	{
		ft_put_error("🍪: export: `");
		ft_put_error(slice1);
		if (found_equal)
			ft_put_error("=");
		ft_put_error(slice2);
		ft_put_error("': not a valid identifier\n");
		*exit_status = 1;
		return ;
	}
	if (append_mod)
		slice1 = ft_substr(slice1, 0, ft_strlen2(slice1) - 1);
	if (ft_env_update(env, slice1, slice2, append_mod))
	{
		if (slice2 && slice2[0])
			ft_env_add(env, slice1, slice2, 1);
		else
			ft_env_add(env, slice1, slice2, 0);
	}
}

void	ft_export(t_env **env, char **cmd_2d, int *exit_status)
{
	int		i;
	t_env	*env_dup;

	*exit_status = 0;
	if (!(cmd_2d[1]))
	{
		env_dup = ft_env_duplicate(*env);
		ft_print_sorted_env(&env_dup);
	}
	i = 0;
	while (cmd_2d[++i])
	{
		ft_export_help(cmd_2d[i], env, exit_status);
	}
}
