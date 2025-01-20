/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:53:27 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/14 18:53:27 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_pipeline(t_cmd_line cmd_line, t_shell *shell,
	int *prev_pipe, pid_t *last_pid)
{
	int	i;
	int	pipe_fd[2];

	i = 0;
	while (i < cmd_line.nb_cmds)
	{
		if (i < cmd_line.nb_cmds - 1)
			if (pipe(pipe_fd) == -1)
				return ;
		if (i == cmd_line.nb_cmds - 1)
			*last_pid = exec_cmd(cmd_line.cmds[i], shell,
					*prev_pipe, STDOUT_FILENO);
		else
			exec_cmd(cmd_line.cmds[i], shell, *prev_pipe, pipe_fd[1]);
		if (*prev_pipe != STDIN_FILENO)
			close(*prev_pipe);
		if (i < cmd_line.nb_cmds - 1)
		{
			close(pipe_fd[1]);
			*prev_pipe = pipe_fd[0];
		}
		i++;
	}
}

void	wait_for_processes(pid_t last_pid, int *status)
{
	if (last_pid > 0)
	{
		waitpid(last_pid, status, 0);
		while (wait(NULL) > 0)
			;
		*status = (*status & 0xFF00) >> 8;
	}
}

int	exec_cmds(t_cmd_line cmd_line, t_shell *shell)
{
	int		status;
	int		prev_pipe;
	pid_t	last_pid;

	prev_pipe = STDIN_FILENO;
	if (cmd_line.nb_cmds == 1
		&& (!cmd_line.cmds[0].args || !cmd_line.cmds[0].args[0]))
	{
		if (cmd_line.cmds[0].nb_redirections > 0)
		{
			status = handle_redirections(cmd_line.cmds[0]);
			update_status(&shell->env, status);
		}
		return (0);
	}
	if (cmd_line.nb_cmds == 1 && is_builtin_cmd(cmd_line.cmds[0].args[0]))
	{
		status = exec_builtin(cmd_line.cmds[0], shell);
		update_status(&shell->env, status);
		return (status);
	}
	execute_pipeline(cmd_line, shell, &prev_pipe, &last_pid);
	wait_for_processes(last_pid, &status);
	update_status(&shell->env, status);
	return (0);
}
