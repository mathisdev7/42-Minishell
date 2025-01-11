/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 02:15:00 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/11 02:15:00 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remove_quotes(char *arg)
{
	char	*clean_arg;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	clean_arg = malloc(sizeof(char) * (ft_strlen(arg) + 1));
	if (!clean_arg)
		return (NULL);
	while (arg[i])
	{
		if (arg[i] != '"' && arg[i] != '\'')
			clean_arg[j++] = arg[i];
		i++;
	}
	clean_arg[j] = '\0';
	return (clean_arg);
}


t_cmd_line parse_cmd_line(char *line)
{
    int i;
    t_cmd_line cmd_line;
    char **splitted_cmds;

    i = 0;
    cmd_line.nb_cmds = 1;
    while (line[i])
    {
        if (line[i] == '|')
            cmd_line.nb_cmds++;
        i++;
    }

    cmd_line.cmds = malloc(sizeof(t_cmd) * cmd_line.nb_cmds);
    if (!cmd_line.cmds)
    {
        cmd_line.nb_cmds = 0;
        return (cmd_line);
    }

    splitted_cmds = ft_split(line, '|');
    i = 0;
    while (i < cmd_line.nb_cmds)
    {
        cmd_line.cmds[i] = parse_cmd(splitted_cmds[i]);
        cmd_line.cmds[i].pipe_presence = (i < cmd_line.nb_cmds - 1) ? 1 : 0;
        i++;
    }
    free_split(splitted_cmds);
    return (cmd_line);
}

t_cmd	parse_cmd(char *cmd_line)
{
	t_cmd	cmd;
	int		i;

	i = 0;
	cmd.args = ft_split_args(cmd_line);
	while (cmd.args[i])
	{
		cmd.args[i] = remove_quotes(cmd.args[i]);
		i++;
	}
	return (cmd);
}