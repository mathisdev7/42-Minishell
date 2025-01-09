/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:40:51 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/09 16:40:51 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_shell(void)
{
	read_history(HISTORY_FILE_PATH);
	loop_shell();
}

void	handle_cmd(char *cmd_line)
{
	int		i;
	char	**cmd;

	i = 0;
	cmd = ft_split(cmd_line, ' ');
	while (cmd[i])
	{
		printf("[%s] ", cmd[i]);
		i++;
	}
	printf("\n");
	i = 0;
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
}

void	loop_shell(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		if (ft_strncmp(line, "exit", ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		handle_cmd(line);
		free(line);
	}
	write_history(HISTORY_FILE_PATH);
}
