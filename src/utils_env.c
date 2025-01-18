/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:00:40 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/18 11:12:20 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_env_var(t_env *env, char *key, char *value)
{
	t_env	*new_var;
	t_env	*current;

	current = env;
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
	new_var->next = env;
	env = new_var;
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

char	*ft_getenv(char *name, t_env *envp)
{
	t_env	*current;

	if (!name || !envp)
		return (NULL);
	current = envp;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*replace_env_var(char *arg, int start, char *value, int var_len)
{
	char	*new_arg;
	int		new_len;

	if (!value)
		value = "";
	new_len = ft_strlen(arg) - (var_len + 1) + ft_strlen(value) + 1;
	new_arg = malloc(sizeof(char) * new_len);
	if (!new_arg)
		return (NULL);
	ft_strlcpy(new_arg, arg, start + 1);
	ft_strlcat(new_arg, value, new_len);
	ft_strlcat(new_arg, arg + start + var_len + 1, new_len);
	return (new_arg);
}
