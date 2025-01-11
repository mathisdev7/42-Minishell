/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 02:20:00 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/11 02:20:00 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*set_full_cmd(char *current_path, char *cmd_name)
{
	char	*full_cmd;
	char	*cmd_path;
	char	slash[2];

	slash[0] = '/';
	slash[1] = '\0';
	cmd_path = ft_strjoin(current_path, slash);
	full_cmd = ft_strjoin(cmd_path, cmd_name);
	free(cmd_path);
	return (full_cmd);
}

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

static char	*check_direct_path(char *cmd_name)
{
	if (cmd_name[0] == '/' || cmd_name[0] == '.')
	{
		if (access(cmd_name, X_OK) == 0)
			return (ft_strdup(cmd_name));
		return (NULL);
	}
	return (NULL);
}

char	*get_cmd_path(t_env *envp, char *cmd_name)
{
	int		i;
	char	**splitted_path;
	char	*full_cmd;
	char	*direct_path;

	direct_path = check_direct_path(cmd_name);
	if (direct_path)
		return (direct_path);
	splitted_path = get_splitted_path(envp);
	if (!splitted_path)
		return (NULL);
	i = 0;
	while (splitted_path[i])
	{
		full_cmd = set_full_cmd(splitted_path[i], cmd_name);
		if (access(full_cmd, X_OK) == 0)
		{
			free_split(splitted_path);
			return (full_cmd);
		}
		free(full_cmd);
		i++;
	}
	free_split(splitted_path);
	return (NULL);
}
