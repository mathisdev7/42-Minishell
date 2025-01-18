/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:52:00 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/18 14:00:26 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	parse_redirections(t_cmd *cmd, char *cmd_line)
{
	int	i;
	int	redir_index;
	int	in_single_quote;
	int	in_double_quote;

	i = 0;
	redir_index = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	cmd->nb_redirections = count_redirections_in_line(cmd_line);
	cmd->redirections = malloc(sizeof(t_redirection) * cmd->nb_redirections);
	if (!cmd->redirections)
		return ;
	while (cmd_line[i])
	{
		toggle_quote_redir(cmd_line[i], &in_single_quote, &in_double_quote);
		if (!in_single_quote && !in_double_quote && (cmd_line[i] == '>'
				|| cmd_line[i] == '<'))
			handle_redirection(cmd, cmd_line, &i, &redir_index);
		i++;
	}
}

static int	is_redirection(char c)
{
	return (c == '>' || c == '<');
}

static int	skip_redirection(const char *cmd_line, int i)
{
	if (cmd_line[i + 1] && is_redirection(cmd_line[i + 1]))
		i++;
	i++;
	while (cmd_line[i] && (cmd_line[i] == ' ' || cmd_line[i] == '\t'))
		i++;
	while (cmd_line[i] && !(cmd_line[i] == ' ' || cmd_line[i] == '\t'
			|| is_redirection(cmd_line[i])))
		i++;
	return (i);
}

int	skip_redirection_target(const char *cmd_line, int i)
{
	while (cmd_line[i] && (cmd_line[i] == ' ' || cmd_line[i] == '\t'))
		i++;
	while (cmd_line[i] && cmd_line[i] != ' ' && cmd_line[i] != '\t'
		&& cmd_line[i] != '>' && cmd_line[i] != '<')
		i++;
	return (i);
}

char	*remove_redirections(char *cmd_line)
{
	int		i;
	int		j;
	int		in_single_quote;
	int		in_double_quote;
	char	*new_cmd_line;

	i = 0;
	j = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	new_cmd_line = malloc(ft_strlen(cmd_line) + 1);
	if (!new_cmd_line)
		return (NULL);
	while (cmd_line[i])
	{
		update_quote_state_redir(cmd_line[i], &in_single_quote,
			&in_double_quote);
		if (!in_single_quote && !in_double_quote && is_redirection(cmd_line[i]))
			i = skip_redirection(cmd_line, i);
		else
			new_cmd_line[j++] = cmd_line[i++];
	}
	new_cmd_line[j] = '\0';
	return (new_cmd_line);
}
