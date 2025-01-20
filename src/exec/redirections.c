/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:00:28 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/20 11:00:28 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	open_redir_file(t_redirection redir)
{
	if (redir.type == 1)
		return (open(redir.file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (redir.type == 2)
		return (open(redir.file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	else if (redir.type == 3)
		return (open(redir.file, O_RDONLY));
	else if (redir.type == 4)
		return (handle_here_doc(redir.file));
	return (-1);
}

int	handle_redirections(t_cmd cmd)
{
	int	i;
	int	fd;

	i = 0;
	while (i < cmd.nb_redirections)
	{
		fd = open_redir_file(cmd.redirections[i]);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(cmd.redirections[i].file);
			if (cmd.args[0])
				exit(1);
			return (1);
		}
		if (!cmd.args[0])
			return (0);
		if (cmd.redirections[i].type == 1 || cmd.redirections[i].type == 2)
			dup2(fd, STDOUT_FILENO);
		else if (cmd.redirections[i].type == 3 || cmd.redirections[i].type == 4)
			dup2(fd, STDIN_FILENO);
		close(fd);
		i++;
	}
	return (0);
}
