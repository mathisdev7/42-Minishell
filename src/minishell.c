/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:56:29 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/11 01:55:32 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_shell(t_env **envp)
{
	loop_shell(envp);
}

int	is_builtin_cmd(char **cmd_args)
{
	if (ft_strcmp(cmd_args[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd_args[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd_args[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd_args[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd_args[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd_args[0], "env") == 0)
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

t_cmd	parse_cmd(char *cmd_line, t_env **envp)
{
	t_cmd	cmd;
	int		i;

	i = 0;
	cmd.args = ft_split_args(cmd_line);
	while (cmd.args[i])
	{
		cmd.args[i] = remove_quotes(cmd.args[i]);
		i++;
	}
	if (is_builtin_cmd(cmd.args))
		exec_builtin(cmd, envp);
	else
		exec_cmd(cmd, envp);
	return (cmd);
}

void	loop_shell(t_env **envp)
{
	char	*line;
	char	cwd[1024];

	while (1)
	{
		// je sais pas i on a le droit mais pour l'instant c'est pas grave
		getcwd(cwd, sizeof(cwd));
		// je pense que tu vas trouver les couleurs atroces mais change les tkt
		printf("\033[38;5;208m[📁] ➾ %s\033[0m", cwd);
		line = readline("\033[38;5;214m ➜\033[0m ");
		if (*line)
			add_history(line);
		if (ft_strcmp(line, "exit") == 0)
		{
			rl_clear_history();
			printf("Bye ✌️\n");
			free(line);
			return ;
		}
		parse_cmd(line, envp);
		free(line);
	}
}
