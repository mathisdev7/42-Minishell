/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:12:26 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/18 11:18:48 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count_env_vars(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static char	*copy_env_var(t_env *current)
{
	char	*tmp;
	char	*env_var;

	tmp = ft_strjoin(current->name, "=");
	env_var = ft_strjoin(tmp, current->value);
	free(tmp);
	return (env_var);
}

char	**env_to_array(t_env *env)
{
	t_env	*current;
	char	**env_array;
	int		size;
	int		i;

	size = count_env_vars(env);
	env_array = malloc(sizeof(char *) * (size + 1));
	if (!env_array)
		return (NULL);
	current = env;
	i = 0;
	while (current)
	{
		env_array[i] = copy_env_var(current);
		if (!env_array[i])
		{
			free_strs(env_array);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
