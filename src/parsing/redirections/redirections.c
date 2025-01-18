/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:51:11 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/18 13:59:51 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	count_redirections_in_line(char *cmd_line)
{
	int	i;
	int	nb_redirections;
	int	in_single_quote;
	int	in_double_quote;

	nb_redirections = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	i = 0;
	while (cmd_line[i])
	{
		update_quote_state(cmd_line[i], &in_single_quote, &in_double_quote);
		if (!in_single_quote && !in_double_quote && (cmd_line[i] == '<'
				|| cmd_line[i] == '>'))
		{
			nb_redirections++;
			if (cmd_line[i + 1] && cmd_line[i] == cmd_line[i + 1])
				i++;
		}
		i++;
	}
	return (nb_redirections);
}

char	*get_redir_file(char *cmd_line, int i)
{
	char	*redir_file;
	int		file_len;
	int		j;

	file_len = 0;
	j = 0;
	while (cmd_line[i] && (cmd_line[i] == 32 || cmd_line[i] == '\t'))
		i++;
	while (cmd_line[file_len] != 32 && cmd_line[file_len] != '\t')
		file_len++;
	redir_file = malloc(sizeof(char) * (file_len + 1));
	if (!redir_file)
		return (NULL);
	while (cmd_line[i] && cmd_line[i] != 32 && cmd_line[i] != '\t')
	{
		redir_file[j] = cmd_line[i];
		i++;
		j++;
	}
	redir_file[j] = '\0';
	return (redir_file);
}

void	toggle_quote_redir(char c, int *in_single_quote,
		int *in_double_quote)
{
	if (c == '\'' && !(*in_double_quote))
		*in_single_quote = !(*in_single_quote);
	else if (c == '"' && !(*in_single_quote))
		*in_double_quote = !(*in_double_quote);
}

static int	get_redirection_type(char *cmd_line, int *i)
{
	if (cmd_line[*i] == '>')
	{
		if (cmd_line[*i + 1] == '>')
		{
			(*i)++;
			return (2);
		}
		return (1);
	}
	if (cmd_line[*i + 1] == '<')
	{
		(*i)++;
		return (4);
	}
	return (3);
}

void	handle_redirection(t_cmd *cmd, char *cmd_line, int *i,
		int *redir_index)
{
	int	type;

	type = get_redirection_type(cmd_line, i);
	cmd->redirections[*redir_index].type = type;
	cmd->redirections[*redir_index].file = remove_quotes_from_str(
			get_redir_file(cmd_line, ++(*i)));
	(*redir_index)++;
}
