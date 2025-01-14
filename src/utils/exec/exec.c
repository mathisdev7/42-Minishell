/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:37:40 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 13:14:47 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_cmd cmd, t_env **envp)
{
	int	status;

	status = 0;
	if (ft_strcmp(cmd.args[0], "cd") == 0)
		status = exec_cd(cmd, envp);
	else if (ft_strcmp(cmd.args[0], "echo") == 0)
		status = exec_echo(cmd, envp);
	else if (ft_strcmp(cmd.args[0], "pwd") == 0)
		status = exec_pwd(cmd);
	else if (ft_strcmp(cmd.args[0], "export") == 0)
		status = exec_export(cmd, envp);
	else if (ft_strcmp(cmd.args[0], "unset") == 0)
		status = exec_unset(cmd, envp);
	else if (ft_strcmp(cmd.args[0], "env") == 0)
		status = exec_env(cmd, envp);
	else if (ft_strcmp(cmd.args[0], "exit") == 0)
		status = exec_exit(cmd, envp);
	return (status);
}
