/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:56:29 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/14 14:53:00 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_shell(t_env **envp)
{
	setup_signals();
	loop_shell(envp);
}

char	*create_prompt(char *cwd)
{
	char	*prompt;

	prompt = ft_strjoin3("\001\033[1;36m\002┌──(\001\033[1;33m\002",
			cwd,
			"\001\033[1;36m\002)\n└─\001\033[1;35m\002❯"
			"\001\033[1;36m\002❯\001\033[1;35m\002❯\001\033[0m\002 ");
	return (prompt);
}

int	handle_empty_line(char *line)
{
	size_t	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (i == ft_strlen(line))
		return (1);
	return (0);
}

void	loop_shell(t_env **envp)
{
	char	*line;
	char	cwd[1024];
	char	*prompt;
	int		status;

	while (1)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("getcwd error");
			return ;
		}
		prompt = create_prompt(cwd);
		line = readline(prompt);
		free(prompt);
		if (!line)
			break ;
		if (!handle_empty_line(line))
		{
			status = process_input(line, envp);
			if (status == -1)
				break ;
		}
	}
}
