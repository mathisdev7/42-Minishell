/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:16:22 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/20 10:16:55 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin_cmd(char *cmd_name)
{
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "exit") == 0)
		return (1);
	return (0);
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
