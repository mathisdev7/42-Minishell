/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:24:09 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 12:24:27 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**get_splitted_path(t_env *envp)
{
	char	*path_value;
	char	**splitted_path;

	path_value = ft_getenv("PATH", envp);
	if (!path_value)
		return (NULL);
	splitted_path = ft_split(path_value, ':');
	if (!splitted_path)
		return (NULL);
	return (splitted_path);
}

char	*check_direct_path(char *cmd_name)
{
	if (cmd_name[0] == '/' || cmd_name[0] == '.')
	{
		if (access(cmd_name, X_OK) == 0)
			return (ft_strdup(cmd_name));
		return (NULL);
	}
	return (NULL);
}
