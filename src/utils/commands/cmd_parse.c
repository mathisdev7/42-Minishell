/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:15:22 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 14:25:29 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_cmd(t_cmd *cmd)
{
	cmd->args = NULL;
	cmd->nb_redirections = 0;
	cmd->redirections = NULL;
}

static int	handle_echo_quotes(t_cmd *cmd, char *cmd_line, t_env *envp, int i)
{
	char	*tmp;

	cmd->args = malloc(sizeof(char *) * 3);
	if (!cmd->args)
		return (0);
	cmd->args[0] = ft_strdup("echo");
	while (cmd_line[i] && (cmd_line[i] == ' ' || cmd_line[i] == '\t'))
		i++;
	if (cmd_line[i] == '"')
		tmp = expand_env_var(cmd_line + i, envp);
	else
		tmp = ft_strdup(cmd_line + i);
	cmd->args[1] = remove_quotes(tmp);
	free(tmp);
	cmd->args[2] = NULL;
	cmd->nb_redirections = 0;
	cmd->redirections = NULL;
	return (1);
}

static void	expand_args(t_cmd *cmd, t_env *envp)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] != '\'')
		{
			tmp = expand_env_var(cmd->args[i], envp);
			if (tmp)
			{
				free(cmd->args[i]);
				cmd->args[i] = tmp;
			}
		}
		i++;
	}
}

static void	remove_arg_quotes(t_cmd *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmd->args[i])
	{
		tmp = remove_quotes(cmd->args[i]);
		free(cmd->args[i]);
		cmd->args[i] = tmp;
		i++;
	}
}

t_cmd	parse_cmd(char *cmd_line, t_env *envp)
{
	t_cmd	cmd;
	int		is_echo;

	init_cmd(&cmd);
	if (is_empty_cmd(cmd_line))
		return (cmd);
	is_echo = (ft_strncmp(cmd_line, "echo", 4) == 0);
	if (is_echo && (ft_strchr(cmd_line, '"') || ft_strchr(cmd_line, '\'')))
	{
		if (!handle_echo_quotes(&cmd, cmd_line, envp, 4))
			return (cmd);
		return (cmd);
	}
	cmd.nb_redirections = 0;
	cmd.redirections = parse_redirection(cmd_line, &cmd.nb_redirections);
	cmd.args = ft_split_args(cmd_line);
	if (!cmd.args)
		return (cmd);
	expand_args(&cmd, envp);
	remove_arg_quotes(&cmd);
	return (cmd);
}
