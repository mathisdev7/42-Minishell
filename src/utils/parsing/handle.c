/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:43:34 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 13:40:30 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_output_redir(t_redirection *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell: open");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (-1);
	}
	return (fd);
}

static int	handle_append_redir(t_redirection *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("minishell: open");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (-1);
	}
	return (fd);
}

static int	handle_input_redir(t_redirection *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("minishell: %s: No such file or directory\n", redir->file);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (-1);
	}
	return (fd);
}

static int	handle_heredoc_redir(t_redirection *redir)
{
	int	fd;

	fd = redir->fd;
	if (fd == -1)
	{
		ft_printf("minishell: error in here-document\n");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (-1);
	}
	return (fd);
}

int	handle_redirections(t_cmd *cmd)
{
	int				fd;
	t_redirection	*redir;
	int				i;

	i = 0;
	while (i < cmd->nb_redirections)
	{
		redir = &cmd->redirections[i];
		if (redir->type == 1)
			fd = handle_output_redir(redir);
		else if (redir->type == 2)
			fd = handle_append_redir(redir);
		else if (redir->type == 3)
			fd = handle_input_redir(redir);
		else if (redir->type == 4)
			fd = handle_heredoc_redir(redir);
		if (fd == -1)
			return (-1);
		close(fd);
		i++;
	}
	return (0);
}
