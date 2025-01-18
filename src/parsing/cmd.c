/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:52:15 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/18 15:20:49 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	parse_cmd(char *cmd_line, t_env *envp, int pipe_presence)
{
	char	**args;
	t_cmd	cmd;

	cmd.nb_redirections = count_redirections_in_line(cmd_line);
	if (cmd.nb_redirections > 0)
	{
		parse_redirections(&cmd, cmd_line);
		cmd_line = remove_redirections(cmd_line);
	}
	args = ft_split_args(remove_out_spaces(cmd_line));
	parse_env_vars(args, envp);
	if (!args)
	{
		ft_printf("minishell: %s not found!\n", cmd_line);
		cmd.args = NULL;
		return (cmd);
	}
	cmd.args = remove_out_quotes(args);
	if (!cmd.args)
	{
		cmd.args = NULL;
		return (ft_printf("minishell: %s not found!\n", cmd_line), cmd);
	}
	cmd.pipe_presence = pipe_presence;
	return (cmd);
}

static int	validate_cmd_line(char *line)
{
	if (!line || !*line)
		return (0);
	if (!are_quotes_close(line, '\'') || !are_quotes_close(line, '"'))
	{
		ft_printf("minishell: Unclosed quotes detected\n");
		return (0);
	}
	if (is_only_spaces(line))
		return (0);
	return (1);
}

static char	**split_cmd_line(char *line)
{
	char	**splitted_cmds;

	splitted_cmds = ft_split(line, '|');
	if (!splitted_cmds)
		ft_printf("minishell: %s not found\n", line);
	return (splitted_cmds);
}

static void	parse_splitted_cmds(t_cmd_line *cmd_line, char **splitted_cmds,
		t_env *envp)
{
	int	i;

	i = 0;
	while (splitted_cmds[cmd_line->nb_cmds])
		cmd_line->nb_cmds++;
	cmd_line->cmds = malloc(sizeof(t_cmd) * (cmd_line->nb_cmds + 1));
	if (!cmd_line->cmds)
		return ;
	while (splitted_cmds[i])
	{
		cmd_line->cmds[i] = parse_cmd(splitted_cmds[i], envp,
				i < cmd_line->nb_cmds - 1);
		i++;
	}
}

t_cmd_line	parse_cmd_line(char *line, t_env *envp)
{
	t_cmd_line	cmd_line;
	char		**splitted_cmds;

	cmd_line.cmds = NULL;
	cmd_line.nb_cmds = 0;
	if (!validate_cmd_line(line))
		return (cmd_line);
	splitted_cmds = split_cmd_line(line);
	if (!splitted_cmds)
		return (cmd_line);
	parse_splitted_cmds(&cmd_line, splitted_cmds, envp);
	return (cmd_line);
}
