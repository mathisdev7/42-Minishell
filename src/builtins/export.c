/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:29:34 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/13 17:15:18 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	print_env(t_env *envp)
{
	t_env	*current;

	current = envp;
	while (current)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	return (1);
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

void	update_status(t_env **envp, int status)
{
	t_env	*current;
	char	*status_str;
	t_env	*new_env;

	status_str = ft_itoa(status);
	if (!status_str)
		return ;
	current = *envp;
	while (current)
	{
		if (ft_strcmp(current->name, "?") == 0)
		{
			free(current->value);
			current->value = status_str;
			return ;
		}
		current = current->next;
	}
	new_env = malloc(sizeof(t_env));
	if (!new_env)
	{
		free(status_str);
		return ;
	}
	new_env->name = ft_strdup("?");
	new_env->value = status_str;
	new_env->next = *envp;
	*envp = new_env;
}

static void	add_env_var(t_env **env_list, char *key, char *value)
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

static void	handle_export_arg(char *arg, t_env **env_list)
{
	char	*equal_sign;
	char	*key;
	char	*value;
	char	*clean_value;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return ;
	*equal_sign = '\0';
	key = arg;
	value = equal_sign + 1;
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
}

int	exec_export(t_cmd cmd, t_env **envp)
{
	if (!cmd.args[1])
		return (print_env(*envp));
	for (int i = 1; cmd.args[i]; i++)
	{
		handle_export_arg(cmd.args[i], envp);
	}
	return (0);
}
