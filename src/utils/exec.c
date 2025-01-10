/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*   Created: 2025/01/09 19:28:44 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/09 19:28:44 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    exec_cmd(t_cmd cmd, t_env **envp)
{
    if (ft_strcmp(cmd.name, "cd") == 0)
    {
        if (cmd.args == NULL || cmd.args[0] == 0)
            exec_cd("none");
        else
            exec_cd(cmd.args[0]);
    }
	else if (ft_strcmp(cmd.name, "echo") == 0)
		exec_echo(cmd, envp);
	else if (ft_strcmp(cmd.name, "pwd") == 0)
		exec_pwd();
	else if (ft_strcmp(cmd.name, "export") == 0)
		exec_export(cmd, envp);
}
