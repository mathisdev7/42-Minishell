/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:56:58 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/14 10:25:35 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_args(int j, int new_line, t_cmd cmd, t_env **envp)
{
	int	i;

	if (!cmd.args)
		return;

	while (cmd.args[j])
	{
		i = 0;
		if (cmd.args[j])
		{
			if (ft_strcmp(cmd.args[j], "$?") == 0)
				ft_printf("%s", ft_getenv("?", *envp));
			else
				print_regular_arg(cmd.args[j], &i, envp);
		}
		if (cmd.args[j + 1])
			ft_printf(" ");
		j++;
	}
	if (new_line)
		ft_printf("\n");
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
