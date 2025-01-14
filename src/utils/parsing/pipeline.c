/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:51:05 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 13:05:16 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_pipeline(t_cmd_line *cmd_line, pid_t **pids)
{
	*pids = malloc(sizeof(pid_t) * cmd_line->nb_cmds);
	if (!*pids)
		return (-1);
	return (0);
}

int	execute_pipeline(t_cmd_line *cmd_line, t_env **envp, pid_t *pids)
{
	int	pipe_fd[2];
	int	prev_pipe_fd;
	int	i;

	prev_pipe_fd = -1;
	i = 0;
	while (i < cmd_line->nb_cmds)
	{
		if (i < cmd_line->nb_cmds - 1 && pipe(pipe_fd) == -1)
		{
			perror("pipe");
			return (-1);
		}
		pids[i] = fork();
		if (pids[i] == 0)
		{
			setup_pipes(&prev_pipe_fd, pipe_fd, i, cmd_line->nb_cmds);
			execute_command(cmd_line->cmds[i], envp);
		}
		manage_pipes(&prev_pipe_fd, pipe_fd, i, cmd_line->nb_cmds);
		i++;
	}
	return (0);
}
