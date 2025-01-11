/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:56:29 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/11 02:51:49 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_shell(t_env **envp)
{
	loop_shell(envp);
}

static char	*create_prompt(char *cwd)
{
	char	*prompt;

	prompt = ft_strjoin3("\001\033[1;36m\002┌──(\001\033[1;33m\002",
			cwd,
			"\001\033[1;36m\002)\n└─\001\033[1;35m\002❯"
			"\001\033[1;36m\002❯\001\033[1;35m\002❯\001\033[0m\002 ");
	return (prompt);
}

static int	handle_empty_line(char *line)
{
	if (!*line)
	{
		free(line);
		return (1);
	}
	return (0);
}

static int	process_input(char *line, t_env **envp)
{
	if (!line)
		return (0);
	if (handle_empty_line(line))
		return (1);
	add_history(line);
	if (ft_strcmp(line, "exit") == 0)
	{
		rl_clear_history();
		printf("\033[1;32mAu revoir! 👋\033[0m\n");
		free(line);
		return (0);
	}
	parse_cmd(line, envp);
	free(line);
	return (1);
}

void	loop_shell(t_env **envp)
{
	char	*line;
	char	cwd[1024];
	char	*prompt;

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
		if (!process_input(line, envp))
			break ;
	}
}
