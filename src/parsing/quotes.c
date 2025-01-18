/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:49:34 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/18 14:02:03 by mazeghou         ###   ########.fr       */
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

int	is_quote(char c, int in_other_quote, char quote_type)
{
	return (c == quote_type && !in_other_quote);
}

void	toggle_quote(int *quote_flag)
{
	*quote_flag = !(*quote_flag);
}

int	process_quotes(char c, int *in_single_quote, int *in_double_quote)
{
	if (c == '\'' && !(*in_double_quote))
		*in_single_quote = !(*in_single_quote);
	else if (c == '"' && !(*in_single_quote))
		*in_double_quote = !(*in_double_quote);
	return (*in_single_quote || *in_double_quote);
}

void	update_quote_state(char c, int *in_single_quote,
		int *in_double_quote)
{
	if (c == '"' && !(*in_single_quote))
		*in_double_quote = !(*in_double_quote);
	else if (c == '\'' && !(*in_double_quote))
		*in_single_quote = !(*in_single_quote);
}
