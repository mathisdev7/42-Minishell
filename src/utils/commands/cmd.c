/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:19:22 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 13:14:26 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **splitted)
{
	int	i;

	i = 0;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd || !cmd->args)
		return ;
	i = 0;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		cmd->args[i] = NULL;
		i++;
	}
	free(cmd->args);
	cmd->args = NULL;
}

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

int	cmd_exists(char *cmd, t_env *envp)
{
	char	*path;

	if (!cmd)
		return (0);
	if (is_builtin_cmd(&cmd))
		return (1);
	path = get_cmd_path(envp, cmd);
	if (path)
	{
		free(path);
		return (1);
	}
	return (0);
}
