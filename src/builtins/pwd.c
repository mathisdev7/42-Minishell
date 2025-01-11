/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:57:35 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/11 02:59:28 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_pwd(t_cmd cmd)
{
	char	current_path[PATH_MAX];

	if (cmd.args[1])
	{
		printf("\033[1;31m[🧭] pwd: too many arguments\033[0m\n");
		return (1);
	}
	if (getcwd(current_path, sizeof(current_path)) != NULL)
		printf("\033[1;32m[🧭] -> %s\033[0m\n", current_path);
	else
	{
		perror("Error retrieving the current directory");
		return (1);
	}
	return (0);
}
