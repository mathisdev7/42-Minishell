/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:15:22 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 14:16:38 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_file_spaces(char *cmd, int *i)
{
	while (cmd[*i] && (cmd[*i] == ' ' || cmd[*i] == '\t'))
		(*i)++;
}

static void	handle_quote_state(char c, int *in_quotes, char *quote_type)
{
	if ((c == '"' || c == '\'') && (!*in_quotes || c == *quote_type))
	{
		*in_quotes = !*in_quotes;
		if (*in_quotes)
			*quote_type = c;
		else
			*quote_type = 0;
	}
}

static int	get_file_len(char *cmd, int *i)
{
	int		start;
	int		in_quotes;
	char	quote_type;

	start = *i;
	in_quotes = 0;
	quote_type = 0;
	while (cmd[*i])
	{
		if ((cmd[*i] == '"' || cmd[*i] == '\'')
			&& (!in_quotes || cmd[*i] == quote_type))
		{
			handle_quote_state(cmd[*i], &in_quotes, &quote_type);
			(*i)++;
			continue ;
		}
		if (!in_quotes && (cmd[*i] == ' ' || cmd[*i] == '\t'
				|| cmd[*i] == '>' || cmd[*i] == '<'))
			break ;
		(*i)++;
	}
	return (*i - start);
}

char	*extract_file_name(char *cmd, int *i)
{
	char	*file;
	int		start;
	int		len;

	skip_file_spaces(cmd, i);
	start = *i;
	len = get_file_len(cmd, i);
	if (len <= 0)
		return (NULL);
	file = malloc(sizeof(char) * (len + 1));
	if (!file)
		return (NULL);
	ft_strlcpy(file, &cmd[start], len + 1);
	return (file);
}
