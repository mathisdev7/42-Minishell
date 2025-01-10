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

void    exec_builtin(t_cmd cmd, t_env **envp)
{
	if (ft_strcmp(cmd.args[0], "cd") == 0)
		exec_cd(cmd, envp);
	else if (ft_strcmp(cmd.args[0], "echo") == 0)
		exec_echo(cmd, envp);
	else if (ft_strcmp(cmd.args[0], "pwd") == 0)
		exec_pwd();
	else if (ft_strcmp(cmd.args[0], "export") == 0)
		exec_export(cmd, envp);	
	else if (ft_strcmp(cmd.args[0], "unset") == 0)
		exec_unset(cmd, envp);
}
/*
void	exec_cmd(t_cmd cmd, t_env **envp)
{
}
*/
