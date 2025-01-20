/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:53:16 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/20 14:16:26 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_quotes(char *line)
{
	if (!are_quotes_close(line, '\'') || !are_quotes_close(line, '"'))
	{
		ft_printf("minishell: Unclosed quotes detected\n");
		return (0);
	}
	return (1);
}

char	**split_cmds(char *line, int *nb_cmds)
{
	char	**splitted_cmds;

	splitted_cmds = split_pipe(line);
	if (!splitted_cmds)
	{
		ft_printf("minishell: %s not found", line);
		return (NULL);
	}
	*nb_cmds = 0;
	while (splitted_cmds[*nb_cmds])
		(*nb_cmds)++;
	return (splitted_cmds);
}

t_cmd	*init_cmds(int nb_cmds)
{
	t_cmd	*cmds;

	cmds = malloc(sizeof(t_cmd) * (nb_cmds + 1));
	if (!cmds)
		return (NULL);
	return (cmds);
}

void	fill_cmds(t_cmd *cmds, char **splitted_cmds, int nb_cmds, t_env *envp)
{
	int	i;
	int	is_last_cmd;

	i = 0;
	while (i < nb_cmds)
	{
		if (i == nb_cmds - 1)
			is_last_cmd = 0;
		else
			is_last_cmd = 1;
		cmds[i] = parse_cmd(splitted_cmds[i], envp, is_last_cmd);
		i++;
	}
}

t_cmd_line	parse_cmd_line(char *line, t_env *envp)
{
	t_cmd_line	cmd_line;
	char		**splitted_cmds;

	cmd_line.cmds = NULL;
	cmd_line.nb_cmds = 0;
	if (!line || !*line || is_only_spaces(line))
		return (cmd_line);
	if (!check_quotes(line))
		return (cmd_line);
	splitted_cmds = split_cmds(line, &cmd_line.nb_cmds);
	if (!splitted_cmds)
		return (cmd_line);
	cmd_line.cmds = init_cmds(cmd_line.nb_cmds);
	if (!cmd_line.cmds)
	{
		free_strs(splitted_cmds);
		return (cmd_line);
	}
	fill_cmds(cmd_line.cmds, splitted_cmds, cmd_line.nb_cmds, envp);
	free_strs(splitted_cmds);
	return (cmd_line);
}
