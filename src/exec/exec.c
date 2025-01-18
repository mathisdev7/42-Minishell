/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:53:27 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/18 15:08:36 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_cmd(t_cmd cmd, t_shell *shell, int in_fd, int out_fd)
{
	return (exec_child_process(cmd, shell, in_fd, out_fd));
}

int	exec_builtin(t_cmd cmd, t_shell *shell)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(cmd.args[0], "echo") == 0)
		ret = exec_echo(cmd);
	else if (ft_strcmp(cmd.args[0], "unset") == 0)
		ret = exec_unset(cmd, &shell->env);
	else if (ft_strcmp(cmd.args[0], "pwd") == 0)
		ret = exec_pwd();
	else if (ft_strcmp(cmd.args[0], "cd") == 0)
		ret = exec_cd(cmd, shell->env);
	else if (ft_strcmp(cmd.args[0], "export") == 0)
		ret = exec_export(cmd, &shell->env);
	else if (ft_strcmp(cmd.args[0], "env") == 0)
		ret = exec_export(cmd, &shell->env);
	else if (ft_strcmp(cmd.args[0], "exit") == 0)
		ret = exec_exit(cmd);
	return (ret);
}

int	handle_builtin_cmd(t_cmd_line cmd_line, t_shell *shell)
{
	int	status;

	status = exec_builtin(cmd_line.cmds[0], shell);
	update_status(&shell->env, status);
	return (status);
}
