/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:07:59 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/10 20:45:43 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_cd(t_cmd cmd, t_env **envp)
{
	char	current_path[PATH_MAX];
	char	*path;

	if (cmd.args[1] == NULL || ft_strcmp(cmd.args[1], "none") == 0)
	{
		path = ft_getenv("HOME", *envp);
		if (path == NULL)
		{
			fprintf(stderr, "Error: HOME variable not found.\n");
			return (1);
		}
		cmd.args[1] = path;
	}
	else if (cmd.args[1][0] == '$')
	{
		path = ft_getenv(cmd.args[1] + 1, *envp);
		if (path == NULL)
		{
			fprintf(stderr, "Error: %s variable not found.\n", cmd.args[1] + 1);
			return (1);
		}
		cmd.args[1] = path;
	}
	if (chdir(cmd.args[1]) != 0)
	{
		perror("[❌] Error");
		return (1);
	}
	if (getcwd(current_path, sizeof(current_path)) != NULL)
		printf("[📁] | Current directory: %s\n", current_path);
	else
	{
		perror("[❌] Error while retrieving the current directory.");
		return (1);
	}
	return (0);
}
