/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:56:29 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/12 00:45:18 by nopareti         ###   ########.fr       */
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
    while (i < cmd_line.nb_cmds)
    {
        printf("\n--- Commande %d ---\n", i + 1);
        j = 0;
        if (cmd_line.cmds[i].args)
        {
            while (cmd_line.cmds[i].args[j])
            {
                printf("Argument %d: [%s]\n", j + 1, cmd_line.cmds[i].args[j]);
                j++;
            }
            printf("Pipe présent: %s\n", 
                cmd_line.cmds[i].pipe_presence ? "Oui" : "Non");
            printf("Nombre total d'arguments: %d\n", j);
        }
        else
        {
            printf("Pas d'arguments pour cette commande\n");
        }
        printf("------------------\n");
        i++;
    }
    printf("\nNombre total de commandes: %d\n", cmd_line.nb_cmds);
    printf("=== FIN DU PARSING ===\n\n");
}

void    free_cmd(t_cmd *cmd)
{
    int i;

    if (!cmd || !cmd->args)
        return;
    i = 0;
    while (cmd->args[i])
    {
        free(cmd->args[i]);
        cmd->args[i] = NULL;
        i++;
    }
    free(cmd->args);
    cmd->args = NULL;
}

int cmd_exists(char *cmd, t_env *envp)
{
    char *path;
    
    if (!cmd)
        return (0);
    if (is_builtin_cmd(&cmd))
        return (1);
    path = get_cmd_path(envp, cmd);
    if (path)
    {
        free(path);
        return (1);
    }
    return (0);
}

int process_input(char *line, t_env **envp)
{
    t_cmd_line cmd_line;
    pid_t *pids;
    int status;
    int i;
    int pipe_fd[2];
    int prev_pipe_fd = -1;
    int cmd_status = 0;

    if (!line || handle_empty_line(line))
        return (!line ? 0 : 1);
    add_history(line);
    cmd_line = parse_cmd_line(line);
    if (!cmd_line.cmds || cmd_line.nb_cmds == 0)
    {
        free(line);
        return (1);
    }
    if (cmd_line.nb_cmds == 1 && cmd_line.cmds[0].args && 
        ft_strcmp(cmd_line.cmds[0].args[0], "exit") == 0)
    {
        exec_builtin(cmd_line.cmds[0], envp);
        for (i = 0; i < cmd_line.nb_cmds; i++)
            free_cmd(&cmd_line.cmds[i]);
        free(cmd_line.cmds);
        free(line);
        exit(0);
    }
    pids = malloc(sizeof(pid_t) * cmd_line.nb_cmds);
    if (!pids)
    {
        free(line);
        return (1);
    }
    i = 0;
    while (i < cmd_line.nb_cmds)
    {
        if (i < cmd_line.nb_cmds - 1)
        {
            if (pipe(pipe_fd) == -1)
            {
                perror("pipe");
                break;
            }
        }
        pids[i] = fork();
        if (pids[i] == 0)
        {
            if (prev_pipe_fd != -1)
            {
                dup2(prev_pipe_fd, STDIN_FILENO);
                close(prev_pipe_fd);
            }
            if (i < cmd_line.nb_cmds - 1)
            {
                close(pipe_fd[0]);
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
            }
            if (is_builtin_cmd(cmd_line.cmds[i].args))
			{
                exec_builtin(cmd_line.cmds[i], envp);
				exit(0);
            }
            else if (!cmd_exists(cmd_line.cmds[i].args[0], *envp))
            {
                fprintf(stderr, "minishell: %s: command not found\n", 
                    cmd_line.cmds[i].args[0]);
                exit(127);
            }
            else
			{
                exec_cmd(cmd_line.cmds[i], envp);
				exit(0);
			}
            exit(EXIT_FAILURE);
        }

        if (prev_pipe_fd != -1)
            close(prev_pipe_fd);
            
        if (i < cmd_line.nb_cmds - 1)
        {
            close(pipe_fd[1]);
            prev_pipe_fd = pipe_fd[0];
        }

        i++;
    }
    i = 0;
    while (i < cmd_line.nb_cmds)
    {
        waitpid(pids[i], &status, 0);
        if (WIFEXITED(status))
            cmd_status = WEXITSTATUS(status);
        if (cmd_status != 0)
            update_status(envp, cmd_status);
		else
			update_status(envp, 0);
        i++;
    }
    free(pids);
    for (i = 0; i < cmd_line.nb_cmds; i++)
        free_cmd(&cmd_line.cmds[i]);
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
