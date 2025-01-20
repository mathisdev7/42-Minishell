/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:58:40 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/20 13:36:11 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_cmd	handle_cleaned_line(t_cmd cmd, char *cmd_line,
		char *tmp_cmd_line)
{
	char	*cleaned_line;

	cleaned_line = remove_out_spaces(cmd_line);
	if (cmd.nb_redirections > 0)
		free(tmp_cmd_line);
	if (!cleaned_line)
	{
		if (cmd.redirections)
			free(cmd.redirections);
		free(cleaned_line);
		return (cmd);
	}
	free(cleaned_line);
	return (cmd);
}

static t_cmd	handle_args_part(t_cmd cmd, char *cleaned_line, t_env *envp)
{
	char	**args;

	args = ft_split_args(cleaned_line);
	free(cleaned_line);
	if (!args)
	{
		if (cmd.redirections)
			free(cmd.redirections);
		return (cmd);
	}
	parse_env_vars(args, envp);
	cmd.args = remove_out_quotes(args);
	free_strs(args);
	return (cmd);
}

static t_cmd	handle_redirections_part(t_cmd cmd, char *cmd_line,
		char **tmp_cmd_line)
{
	cmd.redirections = malloc(sizeof(t_redirection) * cmd.nb_redirections);
	if (!cmd.redirections)
		return (cmd);
	parse_redirections(&cmd, cmd_line);
	*tmp_cmd_line = remove_redirections(cmd_line);
	if (!*tmp_cmd_line)
	{
		free(cmd.redirections);
		cmd.redirections = NULL;
	}
	return (cmd);
}

t_cmd	parse_cmd(char *cmd_line, t_env *envp, int pipe_presence)
{
	t_cmd	cmd;
	char	*cleaned_line;
	char	*tmp_cmd_line;

	cmd.nb_redirections = count_redirections(cmd_line);
	cmd.redirections = NULL;
	cmd.args = NULL;
	if (cmd.nb_redirections > 0)
	{
		cmd = handle_redirections_part(cmd, cmd_line, &tmp_cmd_line);
		if (!cmd.redirections || !tmp_cmd_line)
			return (cmd);
		cmd_line = tmp_cmd_line;
	}
	cleaned_line = remove_out_spaces(cmd_line);
	cmd = handle_cleaned_line(cmd, cmd_line, tmp_cmd_line);
	if (!cleaned_line)
		return (cmd);
	cmd = handle_args_part(cmd, cleaned_line, envp);
	cmd.pipe_presence = pipe_presence;
	return (cmd);
}
