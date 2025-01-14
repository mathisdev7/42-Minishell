/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:29:34 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 14:17:45 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_env	*update_env(t_env **envp, char *name, char *value)
{
	t_env	*current;
	t_env	*new_env;

	current = *envp;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return (*envp);
		}
		current = current->next;
	}
	new_env = malloc(sizeof(t_env));
	if (!new_env)
	{
		perror("malloc");
		return (NULL);
	}
	new_env->name = ft_strdup(name);
	new_env->value = ft_strdup(value);
	new_env->next = *envp;
	*envp = new_env;
	return (*envp);
}

void	add_env_var(t_env **env_list, char *key, char *value)
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

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	exec_export(t_cmd cmd, t_env **envp)
{
	int	status;
	int	i;

	status = 0;
	if (!cmd.args[1])
		return (print_env(*envp));
	i = 1;
	while (cmd.args[i])
	{
		if (ft_strchr(cmd.args[i], '='))
			status |= handle_export_arg(cmd.args[i], envp);
		else if (!is_valid_identifier(cmd.args[i]))
		{
			ft_putstr_fd("export: '", 2);
			ft_putstr_fd(cmd.args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1;
		}
		else
			add_env_var(envp, cmd.args[i], "");
		i++;
	}
	return (status);
}
