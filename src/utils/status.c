/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:21:05 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 12:28:17 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_env	*create_status_env(char *status_str)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
	{
		free(status_str);
		return (NULL);
	}
	new_env->name = ft_strdup("?");
	new_env->value = status_str;
	return (new_env);
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
	new_env = create_status_env(status_str);
	if (!new_env)
		return ;
	new_env->next = *envp;
	*envp = new_env;
}
