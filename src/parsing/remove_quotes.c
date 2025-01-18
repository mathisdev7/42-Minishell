/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:50:04 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/18 14:44:23 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_escaped_char(t_quote_state *state)
{
	return (state->i > 0 && state->str[state->i - 1] == '\\');
}

static void	handle_single_quote(t_quote_state *state)
{
	if (!state->in_single_quote && (state->i == 0 || !is_escaped_char(state)))
		state->in_single_quote = 1;
	else if (state->in_single_quote)
		state->in_single_quote = 0;
	else
		state->result[state->j++] = state->str[state->i];
}

static void	handle_double_quote(t_quote_state *state)
{
	if (!state->in_double_quote && (state->i == 0 || !is_escaped_char(state)))
		state->in_double_quote = 1;
	else if (state->in_double_quote)
		state->in_double_quote = 0;
	else
		state->result[state->j++] = state->str[state->i];
}

char	*remove_quotes_from_str(char *str)
{
	t_quote_state	state;

	if (!str)
		return (NULL);
	state.str = str;
	state.len = ft_strlen(str);
	state.result = malloc(sizeof(char) * (state.len + 1));
	if (!state.result)
		return (NULL);
	state.i = 0;
	state.j = 0;
	state.in_single_quote = 0;
	state.in_double_quote = 0;
	while (state.str[state.i])
	{
		if (state.str[state.i] == '\'' && !state.in_double_quote)
			handle_single_quote(&state);
		else if (state.str[state.i] == '"' && !state.in_single_quote)
			handle_double_quote(&state);
		else
			state.result[state.j++] = state.str[state.i];
		state.i++;
	}
	state.result[state.j] = '\0';
	return (state.result);
}

char	**remove_out_quotes(char **args)
{
	int		i;
	int		len;
	char	**new_args;
	char	*tmp;

	if (!args)
		return (NULL);
	len = 0;
	while (args[len])
		len++;
	new_args = malloc(sizeof(char *) * (len + 1));
	if (!new_args)
		return (NULL);
	i = 0;
	while (args[i])
	{
		tmp = remove_quotes_from_str(args[i]);
		if (!tmp)
			return (free_strs(new_args), NULL);
		new_args[i] = tmp;
		i++;
	}
	new_args[i] = NULL;
	return (new_args);
}
