/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:02:32 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/18 15:02:35 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	create_pipe(t_cmd_exec *cmd_exec)
{
	if (pipe(cmd_exec->pipe_fd) == -1)
	{
		perror("minishell: pipe");
		return (1);
	}
	return (0);
}

static pid_t	exec_cmd_at_index(t_cmd cmd, t_shell *shell,
		t_cmd_exec *cmd_exec)
{
	if (cmd_exec->pipe_fd[0] != -1 && cmd_exec->pipe_fd[1] != -1)
		return (exec_cmd(cmd, shell, cmd_exec->prev_pipe,
				cmd_exec->pipe_fd[1]));
	else
		return (exec_cmd(cmd, shell, cmd_exec->prev_pipe, STDOUT_FILENO));
}

static void	close_pipe_if_needed(t_cmd_exec *cmd_exec, int nb_cmds)
{
	if (cmd_exec->prev_pipe != STDIN_FILENO)
		close(cmd_exec->prev_pipe);
	if (cmd_exec->i < nb_cmds - 1)
	{
		close(cmd_exec->pipe_fd[1]);
	}
}

static void	wait_for_process_and_update_status(pid_t last_pid, int *status,
		t_shell *shell)
{
	if (last_pid > 0)
	{
		waitpid(last_pid, status, 0);
		while (wait(NULL) > 0)
			;
		if (WIFEXITED(*status))
			*status = WEXITSTATUS(*status);
	}
	update_status(&shell->env, *status);
}

int	exec_cmds(t_cmd_line cmd_line, t_shell *shell)
{
	t_cmd_exec	cmd_exec;

	cmd_exec.i = 0;
	cmd_exec.prev_pipe = STDIN_FILENO;
	if (is_builtin_cmd(cmd_line.cmds[0].args[0]) && cmd_line.nb_cmds == 1)
		return (handle_builtin_cmd(cmd_line, shell));
	while (cmd_exec.i < cmd_line.nb_cmds)
	{
		if (cmd_exec.i < cmd_line.nb_cmds - 1 && create_pipe(&cmd_exec))
			return (1);
		cmd_exec.last_pid = exec_cmd_at_index(cmd_line.cmds[cmd_exec.i], shell,
				&cmd_exec);
		close_pipe_if_needed(&cmd_exec, cmd_line.nb_cmds);
		if (cmd_exec.i < cmd_line.nb_cmds - 1)
			cmd_exec.prev_pipe = cmd_exec.pipe_fd[0];
		cmd_exec.i++;
	}
	wait_for_process_and_update_status(cmd_exec.last_pid, &cmd_exec.status,
		shell);
	return (0);
}
