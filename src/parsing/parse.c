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

int	count_redirections(char **cmd_args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd_args[i])
	{
		if (strcmp(cmd_args[i], ">") == 0 || strcmp(cmd_args[i], ">>") == 0
			|| strcmp(cmd_args[i], "<") == 0 || strcmp(cmd_args[i], "<<") == 0)
			count++;
		i++;
	}
	return (count);
}

void remove_arg(char **cmd_args, int index)
{
    int i = index;

    while (cmd_args[i])
    {
        cmd_args[i] = cmd_args[i + 1];
        i++;
    }
}

void parse_here_doc(t_redirection *redirection, char *delimiter)
{
    int pipe_fd[2];
    char *line;

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    while (1) {
        line = readline("[📝] mini_here_doc> ");
        if (!line || strcmp(line, delimiter) == 0) {
            free(line);
            break;
        }
        write(pipe_fd[1], line, strlen(line));
        write(pipe_fd[1], "\n", 1);
        free(line);
    }
    close(pipe_fd[1]);
    redirection->fd = pipe_fd[0];
    redirection->type = 4;
}

t_redirection *parse_redirection(char **cmd_args, int *nb_redirections)
{
    int i = 0;
    int redir_index = 0;
    t_redirection *redirections;

    *nb_redirections = count_redirections(cmd_args);
    if (*nb_redirections == 0)
        return (NULL);

    redirections = malloc(sizeof(t_redirection) * (*nb_redirections));
    if (!redirections)
        return (NULL);

    while (cmd_args[i])
    {
        if (strcmp(cmd_args[i], ">") == 0 || strcmp(cmd_args[i], ">>") == 0
            || strcmp(cmd_args[i], "<") == 0 || strcmp(cmd_args[i], "<<") == 0)
        {
            if (strcmp(cmd_args[i], "<<") == 0)
            {
                if (cmd_args[i + 1])
                {
                    parse_here_doc(&redirections[redir_index], cmd_args[i + 1]);
                    remove_arg(cmd_args, i);
                    remove_arg(cmd_args, i);
                    redir_index++;
                }
                else
                {
                    fprintf(stderr, "Erreur : here-document sans délimiteur\n");
                    free(redirections);
                    return (NULL);
                }
            }
            else
            {
                redirections[redir_index].type =
                    (strcmp(cmd_args[i], ">") == 0) ? 1 :
                    (strcmp(cmd_args[i], ">>") == 0) ? 2 : 3;

                if (cmd_args[i + 1])
                {
                    redirections[redir_index].file = strdup(cmd_args[i + 1]);
                    redirections[redir_index].fd = -1;
                    remove_arg(cmd_args, i);
                    remove_arg(cmd_args, i);
                    redir_index++;
                }
                else
                {
                    fprintf(stderr, "Erreur : redirection sans fichier\n");
                    free(redirections);
                    return (NULL);
                }
            }
        }
        else
            i++;
    }

    return (redirections);
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
		cmd_line.cmds[i].redirections = parse_redirection(cmd_line.cmds[i].args, &cmd_line.cmds[i].nb_redirections);
        i++;
    }
    free_split(splitted_cmds);
    return (cmd_line);
}

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

t_cmd	parse_cmd(char *cmd_line)
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
	return (cmd);
}
