/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 02:15:00 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/12 00:17:42 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_empty_cmd(char *cmd_line)
{
	int	i;

	if (!cmd_line)
		return (1);
	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] != ' ' && cmd_line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

t_cmd	parse_cmd(char *cmd_line, t_env **envp)
{
	t_cmd	cmd;
	int		i;

	i = 0;
	if (is_empty_cmd(cmd_line))
	{
		cmd.args = NULL;
		return (cmd);
	}
	cmd.args = ft_split_args(cmd_line);
	if (!cmd.args)
	{
		cmd.args = NULL;
		return (cmd);
	}
	while (cmd.args[i])
	{
		cmd.args[i] = remove_quotes(cmd.args[i]);
		i++;
	}
	if (is_builtin_cmd(cmd.args))
		exec_builtin(cmd, envp);
	else
		exec_cmd(cmd, envp);
	return (cmd);
}
