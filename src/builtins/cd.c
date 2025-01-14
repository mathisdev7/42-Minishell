/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:07:59 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 10:28:01 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_home_directory(t_env **envp, char **path)
{
	*path = ft_getenv("HOME", *envp);
	if (*path == NULL)
	{
		ft_printf("Error: HOME variable not found.\n");
		return (1);
	}
	return (0);
}

static int	handle_env_variable(char *arg, t_env **envp, char **path)
{
	*path = ft_getenv(arg + 1, *envp);
	if (*path == NULL)
	{
		ft_printf("Error: %s variable not found.\n", arg + 1);
		return (1);
	}
	return (0);
}

static int	change_directory(char *path)
{
	if (chdir(path) != 0)
	{
		perror("[❌] Error");
		return (1);
	}
	return (0);
}

int	exec_cd(t_cmd cmd, t_env **envp)
{
	char	current_path[PATH_MAX];
	char	*path;

	if (cmd.args[2])
		return (ft_printf("minishell: cd: too many arguments\n"));

	if (cmd.args[1] == NULL || ft_strcmp(cmd.args[1], "none") == 0)
	{
		if (handle_home_directory(envp, &path))
			return (1);
	}
	else if (cmd.args[1][0] == '$')
	{
		if (handle_env_variable(cmd.args[1], envp, &path))
			return (1);
	}
	else
		path = cmd.args[1];
	if (change_directory(path))
		return (1);
	if (getcwd(current_path, sizeof(current_path)) == NULL)
	{
		perror("[❌] Error while retrieving the current directory.");
		return (1);
	}
	return (0);
}
