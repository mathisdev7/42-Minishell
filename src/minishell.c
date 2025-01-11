/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:56:29 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/11 22:16:50 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_shell(t_env **envp)
{
	setup_signals();
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

void    print_cmd_line(t_cmd_line cmd_line)
{
    int i;
    int j;

    i = 0;
    printf("\n=== DÉBUT DU PARSING ===\n");
    while (cmd_line.cmds[i].args != NULL)
    {
        printf("\n--- Commande %d ---\n", i + 1);
        j = 0;
        while (cmd_line.cmds[i].args[j])
        {
            printf("Argument %d: [%s]\n", j + 1, cmd_line.cmds[i].args[j]);
            j++;
        }
        printf("Pipe présent: %s\n", 
            cmd_line.cmds[i].pipe_presence ? "Oui" : "Non");
        printf("Nombre total d'arguments: %d\n", j);
        printf("------------------\n");
        i++;
    }
    printf("\nNombre total de commandes: %d\n", i);
    printf("=== FIN DU PARSING ===\n\n");
}

static int    process_input(char *line, t_env **envp)
{
    t_cmd_line cmd_line;
    int i;

    if (!line)
    {
        printf("\033[1;32mBye! 👋\033[0m\n");
        return (0);
    }
    if (handle_empty_line(line))
    {
        free(line);
        return (1);
    }
    add_history(line);
    cmd_line = parse_cmd_line(line);
    i = 0;
    while (cmd_line.cmds[i].args)
    {
        if (is_builtin_cmd(cmd_line.cmds[i].args))
            exec_builtin(cmd_line.cmds[i], envp);
        else
            exec_cmd(cmd_line.cmds[i], envp);
        free_split(cmd_line.cmds[i].args);
        i++;
    }
    free(cmd_line.cmds);
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
