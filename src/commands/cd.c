/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:07:59 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/10 20:25:18 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_cd(t_cmd cmd, t_env **envp)
{
	char	*path;
	char	*home;

	if (cmd.args[1] == NULL || ft_strcmp(cmd.args[1], "~") == 0)
	{
		home = ft_getenv("HOME", *envp);
		if (home == NULL)
		{
			printf("cd: HOME not set\n");
			return ;
		}
		if (chdir(home) != 0)
			perror("cd");
		return ;
	}
	path = cmd.args[1];
	if (chdir(path) != 0)
		perror("cd");
}
