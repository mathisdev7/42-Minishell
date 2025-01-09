/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:56:58 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/09 19:56:58 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_echo(t_cmd cmd)
{
	if (cmd.args[0] == NULL)
	{
		printf("\n");
	}
	if (cmd.args[0] != NULL && cmd.args[0][0] == '$')
	{
		printf("need to implement the env variables\n");
	}
	else if (cmd.args[0] != NULL && ft_strcmp(cmd.args[0], "-n") == 0)
	{
		cmd.args++;
		while (*cmd.args)
		{
			printf("%s", *cmd.args);
			cmd.args++;
		}
	}
	else
	{
		while (*cmd.args)
		{
			printf("%s ", *cmd.args);
			cmd.args++;
		}
		printf("\n");
	}
}