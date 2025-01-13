/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 02:20:00 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/11 02:20:00 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env_remove_if(t_env **begin_list, char *data_ref, int (*cmp)(char *,
			char *))
{
	t_env	*cur;

	if (begin_list == NULL || *begin_list == NULL)
		return ;
	cur = *begin_list;
	if (cmp(cur->name, data_ref) == 0)
	{
		*begin_list = cur->next;
		free(cur->name);
		free(cur->value);
		free(cur);
		ft_env_remove_if(begin_list, data_ref, cmp);
	}
	else
		ft_env_remove_if(&cur->next, data_ref, cmp);
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
		new_node->name = strdup(strtok(envp[i], "="));
		new_node->value = strdup(strtok(NULL, "="));
		new_node->next = env;
		env = new_node;
		i++;
	}
	new_node = malloc(sizeof(t_env));
	new_node->name = strdup("?");
	new_node->value = strdup("0");
	new_node->next = env;
	env = new_node;
	return (env);
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
