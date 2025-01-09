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

void	init_shell(void)
{
	read_history(HISTORY_FILE_PATH);
	loop_shell();
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

char *remove_quotes(char *arg)
{
    char	*clean_arg;
    size_t		i = 0;
	size_t		j = 0;

	clean_arg = malloc(sizeof(char) * (ft_strlen(arg) + 1));
    if (!clean_arg)
        return NULL;
    while (arg[i])
    {
        if (arg[i] != '"' && arg[i] != '\'')
            clean_arg[j++] = arg[i];
        i++;
    }
    clean_arg[j] = '\0';
    return (clean_arg);
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
	cmd.args = malloc(sizeof(char *) * (count_args(cmd_line) + 1));
	cmd.name = splitted_cmd[0];
	while (splitted_cmd[i])
	{
		cmd.args[j] = remove_quotes(splitted_cmd[i]);
		i++;
		j++;
	}
	cmd.args[j] = NULL;
	exec_cmd(cmd);
	free_split(splitted_cmd);
	return (cmd);
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
		if (is_valid_cmd(ft_split(line, ' ')))
            parse_cmd(line);
        else
            printf("not a valid cmd\n");
		free(line);
	}
	write_history(HISTORY_FILE_PATH);
}
