/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:29:34 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/12 19:32:56 by mazeghou         ###   ########.fr       */
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

void update_status(t_env **envp, int status)
{
    t_env *current;
    char *status_str;

    status_str = ft_itoa(status);
    if (!status_str)
        return;

    current = *envp;
    while (current)
    {
        if (ft_strcmp(current->name, "?") == 0)
        {
            free(current->value);
            current->value = status_str;
            return;
        }
        current = current->next;
    }

    t_env *new_env = malloc(sizeof(t_env));
    if (!new_env)
    {
        free(status_str);
        return;
    }
    new_env->name = ft_strdup("?");
    new_env->value = status_str;
    new_env->next = *envp;
    *envp = new_env;
}

int	exec_export(t_cmd cmd, t_env **envp)
{
	char	*arg;
	char	*equal_sign;
	char	*name;
	char	*value;

	if (!cmd.args[1])
		return (print_env(*envp));
	arg = remove_quotes(cmd.args[1]);
	if (!arg)
		return (printf("Erreur lors de la suppression des guillemets\n"));
	equal_sign = strchr(arg, '=');
	if (!equal_sign)
	{
		free(arg);
		return (printf("Usage: export VAR=value\n"));
	}
	*equal_sign = '\0';
	name = arg;
	value = equal_sign + 1;
	*envp = update_env(envp, name, value);
	free(arg);
	return (0);
}
