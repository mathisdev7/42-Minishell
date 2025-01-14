/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:46:13 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 13:13:21 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_pipes(int *prev_pipe_fd, int *pipe_fd, int i, int nb_cmds)
{
	if (*prev_pipe_fd != -1)
	{
		dup2(*prev_pipe_fd, STDIN_FILENO);
		close(*prev_pipe_fd);
	}
	if (i < nb_cmds - 1)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

void	execute_command(t_cmd cmd, t_env **envp)
{
	int	status;

	if (cmd.redirections && handle_redirections(&cmd) == -1)
	{
		ft_printf("minishell: erreur lors du traitement des redirections\n");
		exit(1);
	}
	if (is_builtin_cmd(cmd.args))
	{
		status = exec_builtin(cmd, envp);
		exit(status);
	}
	else if (!cmd_exists(cmd.args[0], *envp))
	{
		ft_printf("minishell: %s: command not found\n", cmd.args[0]);
		exit(127);
	}
	execve(get_cmd_path(*envp, cmd.args[0]), cmd.args, env_to_array(*envp));
	exit(1);
}

void	manage_pipes(int *prev_pipe_fd, int *pipe_fd, int i, int nb_cmds)
{
	if (*prev_pipe_fd != -1)
		close(*prev_pipe_fd);
	if (i < nb_cmds - 1)
	{
		close(pipe_fd[1]);
		*prev_pipe_fd = pipe_fd[0];
	}
}
