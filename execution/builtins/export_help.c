/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zech-chi <zech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 21:30:24 by zech-chi          #+#    #+#             */
/*   Updated: 2024/04/02 03:17:45 by zech-chi         ###   ########.fr       */
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

static char	*ft_get_slice(char *str, int *right, char stop)
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

static char	*ft_remove_plus_from_slice1(char *old_slice1)
{
	char	*new_slice1;

	new_slice1 = ft_substr(old_slice1, 0, ft_strlen2(old_slice1) - 1);
	free(old_slice1);
	return (new_slice1);
}

static void	ft_export_error(char *slice1, char *slice2, int found_equal, int append_mod)
{
	ft_put_error("🍪: export: `");
	ft_put_error(slice1);
	if (found_equal)
		ft_put_error("=");
	else if (append_mod == 1)
		ft_put_error("+");
	ft_put_error(slice2);
	ft_put_error("': not a valid identifier\n");
	free(slice1);
	free(slice2);
}

void	ft_export_help(char *str, t_env **env, int *exit_status)
{
	char	*slice1;
	char	*slice2;
	int		right;
	int		found_equal;
	int		append_mod;

	right = 0;
	slice1 = ft_get_slice(str, &right, '=');
	found_equal = 1 * (str[right] == '=');
	right += 1 * (str[right] == '=');
	append_mod = ft_is_valid_identifier(slice1);
	slice2 = ft_get_slice(str, &right, '\0');
	if (append_mod == -1)
		return (*exit_status = 1, ft_export_error(slice1, slice2, found_equal, append_mod));
	if (append_mod)
		slice1 = ft_remove_plus_from_slice1(slice1);
	if (append_mod && !found_equal)
		return (*exit_status = 1, ft_export_error(slice1, slice2, found_equal, append_mod));
	if (slice1 && !ft_strcmp2(slice1, "_"))
		return (free(slice1), free(slice2));
	if (!found_equal && ft_env_search(*env, slice1))
		return ;
	if (ft_env_update(env, slice1, slice2, append_mod))
	{
		if (slice2 && found_equal)
			ft_env_add(env, slice1, slice2, 1);
		else
			ft_env_add(env, slice1, slice2, 0);
	}
}
