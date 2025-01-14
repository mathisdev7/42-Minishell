/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:02:47 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 13:04:48 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
