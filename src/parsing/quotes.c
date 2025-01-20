/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:17:14 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/20 11:17:20 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	are_quotes_close(char *str, char quote)
{
	int	len;

	len = 0;
	while (*str)
	{
		if (*str == quote)
			len++;
		str++;
	}
	return (len % 2 == 0);
}

void	init_quote_state(t_quote_state *state, size_t *len, char *str)
{
	state->in_single_quote = 0;
	state->in_double_quote = 0;
	state->i = -1;
	state->j = 0;
	*len = ft_strlen(str);
}

char	*remove_quotes_from_str(char *str)
{
	t_quote_state	state;
	char			*result;
	size_t			len;

	init_quote_state(&state, &len, str);
	if (len == 0)
		return (strdup(""));
	result = malloc(sizeof(char) * (len + 1));
	if (!result || len == 0)
		return (NULL);
	while (str[++state.i])
	{
		if ((str[state.i] == '\'' && !state.in_double_quote)
				|| (str[state.i] == '"' && !state.in_single_quote))
		{
			if (str[state.i] == '\'' && !state.in_single_quote)
				state.in_single_quote = !state.in_single_quote;
			else if (str[state.i] == '"' && !state.in_double_quote)
				state.in_double_quote = !state.in_double_quote;
		}
		else
			result[state.j++] = str[state.i];
	}
	result[state.j] = '\0';
	return (result);
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
