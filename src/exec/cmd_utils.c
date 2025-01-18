/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:04:48 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/18 15:06:58 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_redirections_and_dup(int in_fd, int out_fd)
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
	return (0);
}

void	execute_builtin_or_external(t_cmd cmd, t_shell *shell, char *cmd_path)
{
	if (is_builtin_cmd(cmd.args[0]))
		exec_builtin(cmd, shell);
	else
		execve(cmd_path, cmd.args, env_to_array(shell->env));
}

pid_t	exec_child_process(t_cmd cmd, t_shell *shell, int in_fd, int out_fd)
{
	pid_t	pid;
	char	*cmd_path;

	pid = fork();
	if (pid == -1)
		return (perror("minishell: fork"), 1);
	if (pid == 0)
	{
		handle_redirections_and_dup(in_fd, out_fd);
		handle_redirections(cmd);
		cmd_path = get_cmd_path(cmd.args[0], ft_getenv("PATH", shell->env));
		if (!cmd_path && !is_builtin_cmd(cmd.args[0]))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd.args[0], 2);
			ft_putendl_fd(": command not found", 2);
			exit(127);
		}
		execute_builtin_or_external(cmd, shell, cmd_path);
		free(cmd_path);
		exit(1);
	}
	return (pid);
}
