/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:15:22 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 14:05:11 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_spaces_and_word(char *str, int *i)
{
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t'
		&& str[*i] != '>' && str[*i] != '<')
		(*i)++;
}

static void	handle_double_redir(char *str, int *i)
{
	*i += 2;
	skip_spaces_and_word(str, i);
}

static void	handle_single_redir(char *str, int *i)
{
	(*i)++;
	skip_spaces_and_word(str, i);
}

void	remove_redir_char(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] == '>')
			handle_double_redir(str, &i);
		else if (str[i] == '<' && str[i + 1] == '<')
			handle_double_redir(str, &i);
		else if (str[i] == '>' || str[i] == '<')
			handle_single_redir(str, &i);
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
}
