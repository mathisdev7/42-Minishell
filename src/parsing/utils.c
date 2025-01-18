/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:54:31 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/18 14:01:07 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	should_copy_char(char c, int in_single_quote, int in_double_quote)
{
	return (!((c == '\'' && !in_double_quote) || (c == '"'
				&& !in_single_quote)));
}

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

void	update_quote_state_redir(char c, int *in_single_quote,
		int *in_double_quote)
{
	if (is_quote(c, *in_double_quote, '\''))
		*in_single_quote = !(*in_single_quote);
	else if (is_quote(c, *in_single_quote, '"'))
		*in_double_quote = !(*in_double_quote);
}
