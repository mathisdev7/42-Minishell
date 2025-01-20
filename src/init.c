/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 03:41:39 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/20 10:47:50 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	shell->env = init_env(envp);
	prompt_system(shell);
	return (shell);
}

void	init_env_states(int *i, t_env **envp)
{
	(*i) = -1;
	(*envp) = NULL;
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	t_env	*new_node;
	char	*env_str;
	char	*equals_pos;
	int		i;

	init_env_states(&i, &env);
	while (envp[++i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (free_env(env), NULL);
		env_str = envp[i];
		equals_pos = ft_strchr(env_str, '=');
		if (!equals_pos)
			return (free(new_node), free_env(env), NULL);
		new_node->name = ft_substr(env_str, 0, equals_pos - env_str);
		new_node->value = ft_strdup(equals_pos + 1);
		if (!new_node->name || !new_node->value)
			return (free(new_node->name), free(new_node->value), free(new_node),
				free_env(env), NULL);
		new_node->next = env;
		env = new_node;
	}
	return (env);
}

void	prompt_system(t_shell *shell)
{
	char		*line;
	char		cwd[1024];
	t_cmd_line	cmd_line;

	while (1)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("minishell: getcwd error");
			return ;
		}
		line = readline("minishell> ");
		if (!line)
			return ;
		cmd_line = parse_cmd_line(line, shell->env);
		if (cmd_line.cmds || cmd_line.nb_cmds > 0)
			exec_cmds(cmd_line, shell);
		free(line);
		free_cmd_line(&cmd_line);
	}
}

void	free_cmd_line(t_cmd_line *cmd_line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (cmd_line->cmds)
	{
		while (i < cmd_line->nb_cmds)
		{
			j = 0;
			free_strs(cmd_line->cmds[i].args);
			while (j < cmd_line->cmds[i].nb_redirections)
			{
				free(cmd_line->cmds[i].redirections[j].file);
				j++;
			}
			free(cmd_line->cmds[i].redirections);
			i++;
		}
		i = 0;
		free(cmd_line->cmds);
	}
}
