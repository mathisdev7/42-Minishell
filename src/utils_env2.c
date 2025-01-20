/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:28:09 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/20 10:28:29 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	count_env_size(int *size, t_env *env)
{
	t_env	*current;

	*size = 0;
	current = env;
	while (current)
	{
		(*size)++;
		current = current->next;
	}
}

char	**env_to_array(t_env *env)
{
	t_env	*current;
	char	**env_array;
	int		size;
	int		i;
	char	*tmp;

	count_env_size(&size, env);
	env_array = malloc(sizeof(char *) * (size + 1));
	if (!env_array)
		return (NULL);
	current = env;
	i = 0;
	while (current)
	{
		tmp = ft_strjoin(current->name, "=");
		env_array[i] = ft_strjoin(tmp, current->value);
		free(tmp);
		if (!env_array[i])
			return (free_strs(env_array), NULL);
		current = current->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
