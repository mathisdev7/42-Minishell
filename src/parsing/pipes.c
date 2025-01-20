/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:21:01 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/20 14:25:09 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	init_split_state(t_split_state *state, char *line)
{
	state->in_single_quote = 0;
	state->in_double_quote = 0;
	state->token_start = line;
	state->count = 0;
}

static void	update_quote_states(char c, t_split_state *state)
{
	if (c == '\'' && !state->in_double_quote)
	{
		state->in_single_quote = !state->in_single_quote;
	}
	else if (c == '"' && !state->in_single_quote)
	{
		state->in_double_quote = !state->in_double_quote;
	}
}

static void	handle_pipe(char **result, char *current, t_split_state *state)
{
	char	*new_str;

	*current = '\0';
	new_str = ft_strdup(state->token_start);
	if (!new_str)
		return ;
	result[state->count++] = new_str;
	state->token_start = current + 1;
}

char	**split_pipe(char *line)
{
	char			**result;
	t_split_state	state;
	char			*current;

	result = malloc(MAX_TOKENS * sizeof(char *));
	if (!result)
		return (NULL);
	init_split_state(&state, line);
	current = line;
	while (*current)
	{
		update_quote_states(*current, &state);
		if (*current == '|' && !state.in_single_quote && !state.in_double_quote)
		{
			handle_pipe(result, current, &state);
			if (state.count >= MAX_TOKENS - 1)
				break ;
		}
		current++;
	}
	result[state.count] = ft_strdup(state.token_start);
	if (!result[state.count])
		return (NULL);
	result[++state.count] = NULL;
	return (result);
}
