/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:45:22 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 14:01:34 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quotes(char c, int *in_quotes, char *quote_type)
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

static void	update_quote_state(char c, int *in_quotes, char *quote_type)
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

static int	get_arg_len(char *str, int *i, int *in_quotes, char *quote_type)
{
	int	len;

	len = 0;
	while (str[*i] && (*in_quotes || (str[*i] != ' ' && str[*i] != '\t')))
	{
		update_quote_state(str[*i], in_quotes, quote_type);
		(*i)++;
		len++;
	}
	return (len);
}

char	*extract_arg(char *str, int *i)
{
	int		start;
	int		len;
	int		in_quotes;
	char	quote_type;
	char	*arg;

	start = *i;
	in_quotes = 0;
	quote_type = 0;
	len = get_arg_len(str, i, &in_quotes, &quote_type);
	arg = malloc(sizeof(char) * (len + 1));
	if (!arg)
		return (NULL);
	ft_strlcpy(arg, &str[start], len + 1);
	return (arg);
}

int	count_args(char *str)
{
	int		count;
	int		i;
	int		in_quotes;
	char	quote_type;

	count = 0;
	i = 0;
	in_quotes = 0;
	quote_type = 0;
	while (str && str[i])
	{
		while (str[i] && !in_quotes && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i])
			count++;
		while (str[i] && (in_quotes || (str[i] != ' ' && str[i] != '\t')))
		{
			handle_quotes(str[i], &in_quotes, &quote_type);
			i++;
		}
	}
	return (count);
}
