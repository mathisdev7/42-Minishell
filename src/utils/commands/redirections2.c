/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:35:22 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 13:46:53 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirection	*init_redirections(int nb_redirections)
{
	t_redirection	*redirections;

	redirections = malloc(sizeof(t_redirection) * nb_redirections);
	if (!redirections)
		return (NULL);
	return (redirections);
}

int	handle_heredoc(t_redirection *redirections, int redir_index,
						char *cmd, int *i)
{
	*i += 2;
	redirections[redir_index].file = extract_file_name(cmd, i);
	if (!redirections[redir_index].file)
		return (0);
	parse_here_doc(&redirections[redir_index], redirections[redir_index].file);
	redirections[redir_index].type = 4;
	return (1);
}

int	handle_append(t_redirection *redirections, int redir_index,
						char *cmd, int *i)
{
	*i += 2;
	redirections[redir_index].type = 2;
	redirections[redir_index].file = extract_file_name(cmd, i);
	if (!redirections[redir_index].file)
		return (0);
	redirections[redir_index].fd = -1;
	return (1);
}

int	handle_simple_redir(t_redirection *redirections, int redir_index,
							char *cmd, int *i)
{
	if (cmd[*i] == '>')
		redirections[redir_index].type = 1;
	else
		redirections[redir_index].type = 3;
	(*i)++;
	redirections[redir_index].file = extract_file_name(cmd, i);
	if (!redirections[redir_index].file)
		return (0);
	redirections[redir_index].fd = -1;
	return (1);
}
