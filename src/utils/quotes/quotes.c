/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:04:16 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 14:13:38 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_quote_state(char c, int *in_quotes, char *quote_type)
{
	if ((c == '\'' || c == '"') && (!*in_quotes || c == *quote_type))
	{
		*in_quotes = !*in_quotes;
		if (*in_quotes)
			*quote_type = c;
		else
			*quote_type = 0;
	}
}

static char	*init_result(char *str)
{
	char	*result;

	if (!str)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!result)
		return (NULL);
	return (result);
}

static void	copy_without_quotes(char *str, char *result, int *i, int *j)
{
	int		in_quotes;
	char	quote_type;

	in_quotes = 0;
	quote_type = 0;
	while (str[*i])
	{
		if ((str[*i] == '\'' || str[*i] == '"')
			&& (!in_quotes || str[*i] == quote_type))
		{
			update_quote_state(str[*i], &in_quotes, &quote_type);
		}
		else
			result[(*j)++] = str[*i];
		(*i)++;
	}
}

char	*remove_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;

	result = init_result(str);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	copy_without_quotes(str, result, &i, &j);
	result[j] = '\0';
	return (result);
}
