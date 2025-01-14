/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:45:51 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 13:11:16 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_single_builtin(t_cmd_line *cmd_line,
t_env **envp, char *line)
{
	int	stdout_copy;
	int	stdin_copy;
	int	status;

	stdout_copy = dup(STDOUT_FILENO);
	stdin_copy = dup(STDIN_FILENO);
	if (cmd_line->cmds[0].redirections)
	{
		if (handle_redirections(&cmd_line->cmds[0]) == -1)
		{
			ft_printf("minishell: error in redirections\n");
			return (1);
		}
	}
	status = exec_builtin(cmd_line->cmds[0], envp);
	update_status(envp, status);
	dup2(stdout_copy, STDOUT_FILENO);
	dup2(stdin_copy, STDIN_FILENO);
	close(stdout_copy);
	close(stdin_copy);
	free_cmd(&cmd_line->cmds[0]);
	free(cmd_line->cmds);
	free(line);
	return (1);
}

static int	handle_exit_command(t_cmd_line *cmd_line, t_env **envp)
{
	int	status;

	if (cmd_line->cmds[cmd_line->nb_cmds - 1].args
		&& ft_strcmp(cmd_line->cmds[cmd_line->nb_cmds - 1].args[0], "exit")
		== 0)
	{
		status = exec_exit(cmd_line->cmds[cmd_line->nb_cmds - 1], envp);
		return (status);
	}
	return (0);
}

static int	wait_for_children(t_cmd_line *cmd_line, pid_t *pids, t_env **envp)
{
	int	status;
	int	last_status;
	int	i;

	last_status = 0;
	i = 0;
	while (i < cmd_line->nb_cmds)
	{
		waitpid(pids[i], &status, 0);
		last_status = status >> 8;
		i++;
	}
	update_status(envp, last_status);
	return (last_status);
}

static int	cleanup_resources(t_cmd_line *cmd_line, pid_t *pids, char *line)
{
	int	i;

	free(pids);
	i = 0;
	while (i < cmd_line->nb_cmds)
	{
		free_cmd(&cmd_line->cmds[i]);
		i++;
	}
	free(cmd_line->cmds);
	free(line);
	return (1);
}

int	process_input(char *line, t_env **envp)
{
	t_cmd_line	cmd_line;
	pid_t		*pids;

	if (handle_empty_line(line))
		return (1);
	add_history(line);
	cmd_line = parse_cmd_line(line, *envp);
	if (cmd_line.nb_cmds == 0)
	{
		free(line);
		return (1);
	}
	if (cmd_line.nb_cmds == 1 && is_builtin_cmd(cmd_line.cmds[0].args))
		return (handle_single_builtin(&cmd_line, envp, line));
	if (handle_exit_command(&cmd_line, envp) == -1)
		return (-1);
	if (init_pipeline(&cmd_line, &pids) == -1)
	{
		free(line);
		return (1);
	}
	execute_pipeline(&cmd_line, envp, pids);
	wait_for_children(&cmd_line, pids, envp);
	return (cleanup_resources(&cmd_line, pids, line));
}
