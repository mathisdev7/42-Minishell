/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 04:52:19 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/20 04:52:19 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_quotes(char c, int *in_single_quote, int *in_double_quote)
{
	if (c == '\'' && !(*in_double_quote))
		*in_single_quote = !(*in_single_quote);
	else if (c == '"' && !(*in_single_quote))
		*in_double_quote = !(*in_double_quote);
}

void	set_redirections(t_cmd *cmd, char *cmd_line, int *i, int redir_index)
{
	char	*tmp;

	if (cmd_line[*i] == '>')
	{
		if (cmd_line[*i + 1] == '>')
		{
			(*i)++;
			cmd->redirections[redir_index].type = 2;
		}
		else
			cmd->redirections[redir_index].type = 1;
	}
	else if (cmd_line[*i] == '<')
	{
		if (cmd_line[*i + 1] == '<')
		{
			(*i)++;
			cmd->redirections[redir_index].type = 4;
		}
		else
			cmd->redirections[redir_index].type = 3;
	}
	tmp = get_redir_file(cmd_line, ++(*i));
	cmd->redirections[redir_index].file = remove_quotes_from_str(tmp);
	free(tmp);
}

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
	while (cmd_line[i])
	{
		handle_quotes(cmd_line[i], &in_single_quote, &in_double_quote);
		if (!in_single_quote && !in_double_quote
			&& (cmd_line[i] == '>' || cmd_line[i] == '<'))
		{
			set_redirections(cmd, cmd_line, &i, redir_index);
			redir_index++;
		}
		i++;
	}
}
