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

int	count_redirections(char *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if ((cmd[i] == '>' && cmd[i + 1] == '>') || 
			(cmd[i] == '<' && cmd[i + 1] == '<'))
		{
			count++;
			i += 2;
		}
		else if (cmd[i] == '>' || cmd[i] == '<')
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}

char *extract_file_name(char *cmd, int *i)
{
	char *file;
	int	start;
	int	len;

	while (cmd[*i] && (cmd[*i] == ' ' || cmd[*i] == '\t'))
		(*i)++;
	start = *i;
	while (cmd[*i] && cmd[*i] != ' ' && cmd[*i] != '\t' 
		   && cmd[*i] != '>' && cmd[*i] != '<')
		(*i)++;
	len = *i - start;
	file = malloc(sizeof(char) * (len + 1));
	if (!file)
		return (NULL);
	strncpy(file, &cmd[start], len);
	file[len] = '\0';
	return (file);
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

int	search_str(char *str, char *to_find)
{
    int i;
    size_t j;

    i = 0;
    while (str[i])
    {
        j = 0;
        if (str[i] == to_find[j])
            while (str[i + j] == to_find[j])
                j++;
        if (j == ft_strlen(to_find) - 1)
            return (1);
        i++;
    }
    return (0);
}

void remove_redir_char(char *str)
{
    int i = 0;
    int j = 0;

    while (str[i])
    {
        if (str[i] == '>' && str[i + 1] == '>')
        {
            i += 2;
            while (str[i] == ' ' || str[i] == '\t')
                i++;
            while (str[i] && str[i] != ' ' && str[i] != '\t' 
                   && str[i] != '>' && str[i] != '<')
                i++;
        }
        else if (str[i] == '<' && str[i + 1] == '<')
        {
            i += 2;
            while (str[i] == ' ' || str[i] == '\t')
                i++;
            while (str[i] && str[i] != ' ' && str[i] != '\t' 
                   && str[i] != '>' && str[i] != '<')
                i++;
        }
        else if (str[i] == '>' || str[i] == '<')
        {
            i++;
            while (str[i] == ' ' || str[i] == '\t')
                i++;
            while (str[i] && str[i] != ' ' && str[i] != '\t' 
                   && str[i] != '>' && str[i] != '<')
                i++;
        }
        else
            str[j++] = str[i++];
    }
    str[j] = '\0';
}

t_redirection *parse_redirection(char *cmd, int *nb_redirections)
{
	int	i = 0;
	int	redir_index = 0;
	t_redirection	*redirections;

	*nb_redirections = count_redirections(cmd);
	if (*nb_redirections == 0)
		return (NULL);

	redirections = malloc(sizeof(t_redirection) * (*nb_redirections));
	if (!redirections)
		return (NULL);

	while (cmd[i])
	{
		if (cmd[i] == '<' && cmd[i + 1] == '<')
		{
			i += 2;
			redirections[redir_index].file = extract_file_name(cmd, &i);
			if (!redirections[redir_index].file)
			{
				free(redirections);
				return (NULL);
			}
			parse_here_doc(&redirections[redir_index], redirections[redir_index].file);
			redirections[redir_index].type = 4;
			redir_index++;
		}
		else if (cmd[i] == '>' && cmd[i + 1] == '>')
		{
			i += 2;
			redirections[redir_index].type = 2;
			redirections[redir_index].file = extract_file_name(cmd, &i);
			if (!redirections[redir_index].file)
			{
				free(redirections);
				return (NULL);
			}
			redirections[redir_index].fd = -1;
			redir_index++;
		}
		else if (cmd[i] == '>' || cmd[i] == '<')
		{
			redirections[redir_index].type = (cmd[i] == '>') ? 1 : 3;
			i++;
			redirections[redir_index].file = extract_file_name(cmd, &i);
			if (!redirections[redir_index].file)
			{
				free(redirections);
				return (NULL);
			}
			redirections[redir_index].fd = -1;
			redir_index++;
		}
		else
			i++;
	}
	remove_redir_char(cmd);
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
        int nb_redirections = 0;
        t_redirection *curr_redir = parse_redirection(splitted_cmds[i], &nb_redirections);
        cmd_line.cmds[i] = parse_cmd(splitted_cmds[i]);
        cmd_line.cmds[i].redirections = curr_redir;
        cmd_line.cmds[i].pipe_presence = (i < cmd_line.nb_cmds - 1) ? 1 : 0;
        cmd_line.cmds[i].nb_redirections = nb_redirections;
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
