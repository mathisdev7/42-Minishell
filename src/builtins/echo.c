/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:56:58 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/12 00:11:36 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_args(int j, int new_line, t_cmd cmd, t_env **envp)
{
	int	i;

	while (cmd.args[j])
	{
		if (is_quoted_with_single(cmd.args[j]))
			print_without_quotes(cmd.args[j]);
		else
		{
			i = 0;
			print_regular_arg(cmd.args[j], &i, envp);
		}
		if (cmd.args[j + 1])
			printf(" ");
		j++;
	}
	if (new_line)
		printf("\n");
}

int	exec_echo(t_cmd cmd, t_env **envp)
{
	int	j;
	int	new_line;

	j = 1;
	new_line = 1;
	if (cmd.args[1] && ft_strcmp(cmd.args[1], "-n") == 0)
	{
		new_line = 0;
		j++;
	}
	print_args(j, new_line, cmd, envp);
	return (0);
}
