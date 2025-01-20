/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:18:51 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/20 12:18:51 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	setup_io_redirections(int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}

void	handle_cmd_not_found(char *cmd_arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_arg, 2);
	ft_putendl_fd(": command not found", 2);
	exit(127);
}

int	exec_cmd(t_cmd cmd, t_shell *shell, int in_fd, int out_fd)
{
	pid_t	pid;
	char	*cmd_path;

	pid = fork();
	if (pid == -1)
		return (perror("minishell: fork"), 1);
	if (pid == 0)
	{
		setup_io_redirections(in_fd, out_fd);
		handle_redirections(cmd);
		if (!cmd.args || !cmd.args[0])
			exit(1);
		cmd_path = get_cmd_path(cmd.args[0], ft_getenv("PATH", shell->env));
		if (!cmd_path && !is_builtin_cmd(cmd.args[0]))
			handle_cmd_not_found(cmd.args[0]);
		if (is_builtin_cmd(cmd.args[0]))
			exec_builtin(cmd, shell);
		else
			execve(cmd_path, cmd.args, env_to_array(shell->env));
		free(cmd_path);
		exit(0);
	}
	return (pid);
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
		ret = exec_exit(cmd, shell);
	return (ret);
}
