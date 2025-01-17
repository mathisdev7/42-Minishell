/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 23:56:15 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/16 23:56:15 by nopareti         ###   ########.fr       */
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
	return (0);
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

/*static int is_valid_identifier(char *str)
{
	int i;

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
}*/



static int handle_export_arg(char *arg, t_env **env_list)
{
	char	*equal_sign;
	char	*key;
	char	*value;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
	{
		return (0);
	}

	*equal_sign = '\0';
	key = arg;
	value = equal_sign + 1;
	if (value && *value)
		add_env_var(env_list, key, value);
	else
		add_env_var(env_list, key, "");
	return (0);
}

int	exec_export(t_cmd cmd, t_env **envp)
{
	int status;

	status = 0;
	if (!cmd.args[1] || ft_strcmp(cmd.args[0], "env") == 0)
		return (print_env(*envp));

	for (int i = 1; cmd.args[i]; i++)
	{
		if (ft_strchr(cmd.args[i], '='))
			status |= handle_export_arg(cmd.args[i], envp);
		else
			add_env_var(envp, cmd.args[i], "");
	}
	return (status);
}

