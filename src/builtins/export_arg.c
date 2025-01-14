/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:11:13 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 14:31:55 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_invalid_identifier(char *arg)
{
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static int	handle_export_value(char *key, char *value, t_env **env_list)
{
	char	*clean_value;

	if (value && *value)
	{
		clean_value = remove_quotes(value);
		if (clean_value)
		{
			add_env_var(env_list, key, clean_value);
			free(clean_value);
		}
	}
	else
		add_env_var(env_list, key, "");
	return (0);
}

int	handle_export_arg(char *arg, t_env **env_list)
{
	char	*equal_sign;
	char	*key;
	char	*value;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
	{
		if (!is_valid_identifier(arg))
		{
			print_invalid_identifier(arg);
			return (1);
		}
		return (0);
	}
	*equal_sign = '\0';
	key = arg;
	value = equal_sign + 1;
	if (!is_valid_identifier(key))
	{
		print_invalid_identifier(arg);
		return (1);
	}
	return (handle_export_value(key, value, env_list));
}
