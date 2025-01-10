/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:07:59 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/10 15:05:21 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_cd(char *path)
{
	char	current_path[PATH_MAX];

	if (path == NULL || ft_strcmp(path, "none") == 0)
	{
		path = getenv("HOME");
		if (path == NULL)
		{
			fprintf(stderr, "Error: HOME variable not found.\n");
			return (1);
		}
	}
	path[ft_strcspn(path, "\n")] = '\0';
	if (chdir(path) != 0)
	{
		perror("[❌] Error");
		return (1);
	}
	if (getcwd(current_path, sizeof(current_path)) != NULL)
		printf("[📁] | Current directory: %s\n", current_path);
	else
	{
		perror("Error while retrieving the current directory.");
		return (1);
	}
	return (0);
}
