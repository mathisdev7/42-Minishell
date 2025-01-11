/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 00:30:00 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/12 00:21:10 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	init_quote_state(t_quote_state *state)
{
	state->in_single = 0;
	state->in_double = 0;
	state->i = 0;
	state->j = 0;
}

static int	should_copy_char(char c, t_quote_state *state)
{
	if (c == '\'')
	{
		if (!state->in_double)
		{
			state->in_single = !state->in_single;
			return (1);
		}
	}
	else if (c == '"')
	{
		if (!state->in_single)
			state->in_double = !state->in_double;
		return (0);
	}
	return (1);
}

char	*remove_quotes(char *arg)
{
	char			*clean_arg;
	t_quote_state	state;

	if (!arg)
		return (NULL);
	clean_arg = malloc(sizeof(char) * (ft_strlen(arg) + 1));
	if (!clean_arg)
		return (NULL);
	init_quote_state(&state);
	while (arg[state.i])
	{
		if (should_copy_char(arg[state.i], &state))
			clean_arg[state.j++] = arg[state.i];
		state.i++;
	}
	clean_arg[state.j] = '\0';
	return (clean_arg);
}
