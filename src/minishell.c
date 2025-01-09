/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:56:29 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/09 14:56:29 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_shell(t_history *history)
{
	loop_shell(history);
}

int	is_valid_cmd(char **splitted_cmd)
{
	if (ft_strcmp(splitted_cmd[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(splitted_cmd[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(splitted_cmd[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(splitted_cmd[0], "export") == 0)
		return (1);
	return (0);
}

t_cmd	parse_cmd(char *cmd_line)
{
	int		i;
	int		j;
	t_cmd	cmd;
	char	**splitted_cmd;

	i = 1;
	j = 0;
	splitted_cmd = ft_split(cmd_line, ' ');
	cmd.args = malloc(sizeof(char *) * (count_cmd(cmd_line) + 1));
	cmd.name = splitted_cmd[0];
	while (splitted_cmd[i])
	{
		cmd.args[j] = splitted_cmd[i];
		i++;
		j++;
	}
	cmd.args[j] = NULL;
	free_split(splitted_cmd);
	return (cmd);
}

void	loop_shell(t_history *history)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (ft_strncmp(line, "exit", ft_strlen(line)) == 0)
			return ;
		add_history(&history, line);
		if (is_valid_cmd(ft_split(line, ' ')))
			parse_cmd(line);
		else
			printf("not a valid cmd\n");
	}
}
