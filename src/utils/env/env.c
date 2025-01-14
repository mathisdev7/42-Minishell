/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:40:53 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 13:14:40 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_env_vars(t_env *envp)
{
	t_env	*current;
	int		count;

	count = 0;
	current = envp;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static int	fill_env_array(char **env_array, t_env *envp)
{
	int		i;
	t_env	*current;

	current = envp;
	i = 0;
	while (current)
	{
		env_array[i] = ft_strjoin3(current->name, "=", current->value);
		if (!env_array[i])
		{
			while (i > 0)
				free(env_array[--i]);
			free(env_array);
			return (0);
		}
		current = current->next;
		i++;
	}
	env_array[i] = NULL;
	return (1);
}

char	**env_to_array(t_env *envp)
{
	char	**env_array;
	int		count;

	count = count_env_vars(envp);
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	if (!fill_env_array(env_array, envp))
		return (NULL);
	return (env_array);
}

void	free_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	t_env	*new_node;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		new_node->name = ft_strdup(strtok(envp[i], "="));
		new_node->value = ft_strdup(strtok(NULL, "="));
		new_node->next = env;
		env = new_node;
		i++;
	}
	new_node = malloc(sizeof(t_env));
	new_node->name = ft_strdup("?");
	new_node->value = ft_strdup("0");
	new_node->next = env;
	env = new_node;
	return (env);
}
