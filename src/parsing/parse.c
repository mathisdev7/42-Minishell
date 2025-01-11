/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 02:15:00 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/11 02:15:00 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remove_quotes(char *arg)
{
	char	*clean_arg;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	clean_arg = malloc(sizeof(char) * (ft_strlen(arg) + 1));
	if (!clean_arg)
		return (NULL);
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
