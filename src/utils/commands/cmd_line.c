/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:30:22 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 13:13:34 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_pipes(char *line)
{
	int		i;
	int		pipe_count;
	int		in_quotes;
	char	quote_type;

	i = 0;
	pipe_count = 0;
	in_quotes = 0;
	quote_type = 0;
	while (line[i])
	{
		handle_quotes(line[i], &in_quotes, &quote_type);
		if (line[i] == '|' && !in_quotes)
			pipe_count++;
		i++;
	}
	return (pipe_count);
}

static t_cmd_line	init_cmd_line(char *line)
{
	t_cmd_line	cmd_line;

	cmd_line.cmds = NULL;
	cmd_line.nb_cmds = 0;
	if (!line || !*line)
		return (cmd_line);
	cmd_line.nb_cmds = count_pipes(line) + 1;
	cmd_line.cmds = ft_calloc(cmd_line.nb_cmds, sizeof(t_cmd));
	if (!cmd_line.cmds)
		cmd_line.nb_cmds = 0;
	return (cmd_line);
}

static void	init_parsing_state(t_parsing_state *state, t_cmd_line *cmd_line,
							char *line, t_env *envp)
{
	state->i = 0;
	state->cmd_index = 0;
	state->in_quotes = 0;
	state->quote_type = 0;
	state->cmd_start = line;
	state->cmd_line = cmd_line;
	state->envp = envp;
}

static void	parse_commands(t_cmd_line *cmd_line, char *line, t_env *envp)
{
	t_parsing_state	state;

	init_parsing_state(&state, cmd_line, line, envp);
	while (line[state.i])
	{
		handle_quotes(line[state.i], &state.in_quotes, &state.quote_type);
		if (line[state.i] == '|' && !state.in_quotes)
		{
			if (state.cmd_index >= cmd_line->nb_cmds)
				break ;
			process_pipe(&state, line);
		}
		state.i++;
	}
	process_final_command(&state, line);
}

t_cmd_line	parse_cmd_line(char *line, t_env *envp)
{
	t_cmd_line	cmd_line;

	cmd_line = init_cmd_line(line);
	if (cmd_line.cmds)
		parse_commands(&cmd_line, line, envp);
	return (cmd_line);
}
