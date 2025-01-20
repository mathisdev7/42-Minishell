/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 23:56:15 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/20 14:09:29 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_env(t_env *envp)
{
	t_env	*current;

	current = envp;
	while (current)
	{
		ft_printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	return (0);
}

static int	is_valid_env_name(const char *name)
{
	int	i;

	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	add_env_var_export(t_env **env_list, char *key, char *value)
{
	t_env	*new_var;
	t_env	*current;

	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->name, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	new_var = malloc(sizeof(t_env));
	if (!new_var)
		return ;
	new_var->name = ft_strdup(key);
	new_var->value = ft_strdup(value);
	new_var->next = *env_list;
	*env_list = new_var;
}

static int	handle_export_arg(char *arg, t_env **env_list)
{
	char	*equal_sign;
	char	*key;
	char	*value;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
	{
		if (!is_valid_env_name(arg))
			return (1);
		add_env_var_export(env_list, arg, "");
		return (0);
	}
	*equal_sign = '\0';
	key = arg;
	value = equal_sign + 1;
	if (!is_valid_env_name(key))
		return (1);
	add_env_var_export(env_list, key, value);
	return (0);
}

int	exec_export(t_cmd cmd, t_env **envp)
{
	int	status;
	int	i;

	status = 0;
	if (!cmd.args[1] || ft_strcmp(cmd.args[0], "env") == 0)
		return (print_env(*envp));
	i = 1;
	while (cmd.args[i])
	{
		if (handle_export_arg(cmd.args[i], envp))
		{
			ft_printf("minishell: export: `%s': not a valid identifier\n",
				cmd.args[i]);
			status = 1;
		}
		i++;
	}
	return (status);
}
