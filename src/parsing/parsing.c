/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 04:39:18 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/20 13:43:57 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_only_spaces(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (0);
		str++;
	}
	return (1);
}

static void	init_quote_state(t_quote_state *state)
{
	state->i = 0;
	state->j = 0;
	state->in_single_quote = 0;
	state->in_double_quote = 0;
}

static void	handle_quotes(char c, t_quote_state *state)
{
	if (c == '\'' && !state->in_double_quote)
		state->in_single_quote = !state->in_single_quote;
	else if (c == '"' && !state->in_single_quote)
		state->in_double_quote = !state->in_double_quote;
}

static void	skip_redirection(char *cmd_line, t_quote_state *state)
{
	if (cmd_line[state->i + 1] == '>' || cmd_line[state->i + 1] == '<')
		state->i++;
	state->i++;
	while (cmd_line[state->i] && (cmd_line[state->i] == ' '
			|| cmd_line[state->i] == '\t'))
		state->i++;
	while (cmd_line[state->i] && cmd_line[state->i] != ' '
		&& cmd_line[state->i] != '\t' && cmd_line[state->i] != '>'
		&& cmd_line[state->i] != '<')
		state->i++;
}

char	*remove_redirections(char *cmd_line)
{
	t_quote_state	state;
	char			*new_cmd_line;

	new_cmd_line = malloc(ft_strlen(cmd_line) + 1);
	if (!new_cmd_line)
		return (NULL);
	init_quote_state(&state);
	while (cmd_line[state.i])
	{
		handle_quotes(cmd_line[state.i], &state);
		if (!state.in_single_quote && !state.in_double_quote
			&& (cmd_line[state.i] == '>' || cmd_line[state.i] == '<'))
			skip_redirection(cmd_line, &state);
		else
			new_cmd_line[state.j++] = cmd_line[state.i++];
	}
	new_cmd_line[state.j] = '\0';
	return (new_cmd_line);
}
