/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 08:35:09 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/16 08:35:09 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_echo(t_cmd cmd)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (!cmd.args[1])
	{
		ft_printf("\n");
		return (0);
	}
	if (ft_strcmp(cmd.args[i], "-n") == 0)
	{
		new_line = 0;
		i++;
	}
	while (cmd.args[i])
	{
		ft_printf("%s", cmd.args[i]);
		if (cmd.args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (new_line)
		ft_printf("\n");
	return (0);
}
