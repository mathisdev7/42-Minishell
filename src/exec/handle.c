/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:48:53 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/18 15:08:42 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	open_redirection_file(t_redirection redir)
{
	int	fd;

	if (redir.type == 1)
		fd = open(redir.file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir.type == 2)
		fd = open(redir.file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir.type == 3)
		fd = open(redir.file, O_RDONLY);
	else if (redir.type == 4)
		fd = handle_here_doc(redir.file);
	else
		fd = -1;
	return (fd);
}

static void	handle_output_redirection(int fd)
{
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	handle_input_redirection(int fd)
{
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	handle_redirections(t_cmd cmd)
{
	int	i;
	int	fd;

	i = 0;
	while (i < cmd.nb_redirections)
	{
		fd = open_redirection_file(cmd.redirections[i]);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(cmd.redirections[i].file);
			exit(1);
		}
		if (cmd.redirections[i].type == 1 || cmd.redirections[i].type == 2)
			handle_output_redirection(fd);
		else if (cmd.redirections[i].type == 3 || cmd.redirections[i].type == 4)
			handle_input_redirection(fd);
		i++;
	}
}

int	handle_here_doc(char *delimiter)
{
	int		here_doc_pipe[2];
	char	*line;

	if (pipe(here_doc_pipe) == -1)
	{
		ft_putstr_fd("minishell: pipe error\n", 2);
		exit(1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, here_doc_pipe[1]);
		free(line);
	}
	close(here_doc_pipe[1]);
	return (here_doc_pipe[0]);
}
