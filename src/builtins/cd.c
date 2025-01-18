/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 23:23:36 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/18 15:20:49 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_home_directory(t_env *env, char **path)
{
	*path = ft_getenv("HOME", env);
	if (*path == NULL)
	{
		ft_printf("Error: HOME variable not found.\n");
		return (1);
	}
	return (0);
}

int	change_directory(char *path)
{
	if (chdir(path) != 0)
	{
		perror("[❌] Error");
		return (1);
	}
	return (0);
}

int	exec_cd(t_cmd cmd, t_env *env)
{
	char	current_path[1024];
	char	*path;

	if (cmd.args[2])
		return (ft_printf("minishell: cd: too many arguments\n"));
	if (cmd.args[1] == NULL || ft_strcmp(cmd.args[1], "none") == 0)
	{
		if (handle_home_directory(env, &path))
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
