/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:33:10 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 13:54:46 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_spaces(char **str)
{
	while (**str == ' ' || **str == '\t')
		(*str)++;
}

static void	update_command(t_cmd *cmd, char *cmd_str, t_env *envp, int has_pipe)
{
	*cmd = parse_cmd(cmd_str, envp);
	cmd->pipe_presence = has_pipe;
}

void	process_pipe(t_parsing_state *state, char *line)
{
	line[state->i] = '\0';
	update_command(&state->cmd_line->cmds[state->cmd_index],
		state->cmd_start, state->envp, 1);
	state->cmd_start = line + state->i + 1;
	skip_spaces(&state->cmd_start);
	state->cmd_index++;
	line[state->i] = '|';
}

void	process_final_command(t_parsing_state *state, char *line)
{
	if (state->cmd_start < line + state->i
		&& state->cmd_index < state->cmd_line->nb_cmds)
		update_command(&state->cmd_line->cmds[state->cmd_index],
			state->cmd_start, state->envp, 0);
}
