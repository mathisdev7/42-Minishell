/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:35:22 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 14:02:08 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_redir(t_redirection *redirections, int *redir_index,
							char *cmd, int *i)
{
	if (cmd[*i] == '<' && cmd[*i + 1] == '<')
	{
		if (!handle_heredoc(redirections, *redir_index, cmd, i))
			return (0);
		(*redir_index)++;
	}
	else if (cmd[*i] == '>' && cmd[*i + 1] == '>')
	{
		if (!handle_append(redirections, *redir_index, cmd, i))
			return (0);
		(*redir_index)++;
	}
	else if (cmd[*i] == '>' || cmd[*i] == '<')
	{
		if (!handle_simple_redir(redirections, *redir_index, cmd, i))
			return (0);
		(*redir_index)++;
	}
	return (1);
}

static t_redirection	*init_parse_redirection(char *cmd, int *nb_redirections,
										int *redir_index)
{
	t_redirection	*redirections;

	*redir_index = 0;
	*nb_redirections = count_redirections(cmd);
	if (*nb_redirections == 0)
		return (NULL);
	redirections = init_redirections(*nb_redirections);
	if (!redirections)
		return (NULL);
	return (redirections);
}

t_redirection	*parse_redirection(char *cmd, int *nb_redirections)
{
	int				i;
	int				redir_index;
	t_redirection	*redirections;
	int				in_quotes;
	char			quote_type;

	redirections = init_parse_redirection(cmd, nb_redirections, &redir_index);
	if (!redirections)
		return (NULL);
	i = 0;
	in_quotes = 0;
	quote_type = 0;
	while (cmd[i])
	{
		handle_quotes(cmd[i], &in_quotes, &quote_type);
		if (!in_quotes && !process_redir(redirections, &redir_index, cmd, &i))
		{
			free(redirections);
			return (NULL);
		}
		if (cmd[i])
			i++;
	}
	remove_redir_char(cmd);
	return (redirections);
}
