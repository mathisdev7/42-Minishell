/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 03:41:39 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/14 03:41:39 by nopareti         ###   ########.fr       */
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

t_env	*init_env(char **envp)
{
	t_env	*env;
	t_env	*new_node;
	int		i;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		new_node->name = ft_strdup(ft_strtok(envp[i], '='));
		new_node->value = ft_strdup(ft_strtok(NULL, '='));
		new_node->next = env;
		env = new_node;
		i++;
	}
	new_node = malloc(sizeof(t_env));
	new_node->name = ft_strdup("?");
	new_node->value = ft_strdup("0");
	new_node->next = env;
	env = new_node;
	return (env);
}

void	prompt_system(t_shell *shell)
{
	char	*line;
	char	cwd[1024];
	t_cmd_line	cmd_line;
	//int		status;

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
		{
			//print_cmd_args(cmd_line.cmds[0]);
			//printf("\n%d\n", cmd_line.cmds[0].nb_redirections);
			//print_redirections(cmd_line.cmds[0]);
			exec_cmds(cmd_line, shell);
		}
		free(line);
		
	}
}