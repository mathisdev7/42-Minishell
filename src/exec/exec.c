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

int	exec_cmd(t_cmd cmd, t_shell *shell, int in_fd, int out_fd)
{
	char	*cmd_path;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("minishell: fork"), 1);
	if (pid == 0)
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
		cmd_path = get_cmd_path(cmd.args[0], ft_getenv("PATH", shell->env));
		if (!cmd_path)
		{
			printf("minishell: %s not found!\n", cmd.args[0]);
			exit(127);
		}
		execve(cmd_path, cmd.args, env_to_array(shell->env));
		free(cmd_path);
		exit(1);
	}
	return (pid);
}

int	exec_cmds(t_cmd_line cmd_line, t_shell *shell)
{
	int	i;
	int	status;
	int	pipe_fd[2];
	int	prev_pipe;
	pid_t	last_pid;

	i = 0;
	prev_pipe = STDIN_FILENO;
	while (i < cmd_line.nb_cmds)
	{
		if (i < cmd_line.nb_cmds - 1)
		{
			if (pipe(pipe_fd) == -1)
				return (perror("minishell: pipe"), 1);
		}
		if (i == cmd_line.nb_cmds - 1)
			last_pid = exec_cmd(cmd_line.cmds[i], shell, prev_pipe, STDOUT_FILENO);
		else
			exec_cmd(cmd_line.cmds[i], shell, prev_pipe, pipe_fd[1]);
		if (prev_pipe != STDIN_FILENO)
			close(prev_pipe);
		if (i < cmd_line.nb_cmds - 1)
		{
			close(pipe_fd[1]);
			prev_pipe = pipe_fd[0];
		}
		i++;
	}
	waitpid(last_pid, &status, 0);
	while (wait(NULL) > 0)
		;
	return (status);
}