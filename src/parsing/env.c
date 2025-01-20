/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:40:23 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/20 13:46:00 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_question_mark(t_env_parse_state *state)
{
	state->k++;
	state->var_name = ft_strdup("?");
}

static void	handle_variable_name(t_env_parse_state *state, char **args)
{
	while (args[state->i][state->k] && (ft_isalnum(args[state->i][state->k])
			|| args[state->i][state->k] == '_'))
		state->k++;
	state->var_name = ft_substr(args[state->i], state->j + 1, state->k
			- (state->j + 1));
}

static void	replace_variable(t_env_parse_state *state, char **args, char *value)
{
	state->new_arg = replace_env_var(args[state->i], state->j, value, state->k
			- (state->j + 1));
	if (state->new_arg)
	{
		free(args[state->i]);
		args[state->i] = state->new_arg;
		if (value)
			state->j += ft_strlen(value) - 1;
		else
			state->j -= 1;
	}
}

static void	process_env_var(t_env_parse_state *state, char **args, t_env *envp)
{
	state->k = state->j + 1;
	if (args[state->i][state->k] == '?')
		handle_question_mark(state);
	else
		handle_variable_name(state, args);
	if (state->var_name)
	{
		state->var_value = ft_getenv(state->var_name, envp);
		if (state->var_value)
			replace_variable(state, args, state->var_value);
		else
			replace_variable(state, args, "");
		free(state->var_name);
	}
}

void	parse_env_vars(char **args, t_env *envp)
{
	t_env_parse_state	state;

	state.i = 0;
	while (args[state.i])
	{
		state.j = 0;
		state.in_single_quote = 0;
		while (args[state.i][state.j])
		{
			if (args[state.i][state.j] == '\'')
				state.in_single_quote = !state.in_single_quote;
			if (!state.in_single_quote && args[state.i][state.j] == '$'
				&& args[state.i][state.j + 1])
				process_env_var(&state, args, envp);
			state.j++;
		}
		state.i++;
	}
}
