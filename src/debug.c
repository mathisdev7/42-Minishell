/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 04:19:05 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/18 15:20:49 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_cmd_args(t_cmd cmd)
{
	int	i;

	i = 0;
	if (!cmd.args)
	{
		return ;
	}
	while (cmd.args[i])
	{
		ft_printf("[%s], ", cmd.args[i]);
		i++;
	}
	ft_printf("\n");
}

void	print_redirections(t_cmd cmd)
{
	int	i;

	if (!cmd.redirections || cmd.nb_redirections == 0)
	{
		ft_printf("No redirections\n");
		return ;
	}
	i = 0;
	while (i < cmd.nb_redirections)
	{
		ft_printf("Redirection %d: ", i + 1);
		if (cmd.redirections[i].type == 1)
			ft_printf("Type: >, ");
		else if (cmd.redirections[i].type == 2)
			ft_printf("Type: >>, ");
		else if (cmd.redirections[i].type == 3)
			ft_printf("Type: <, ");
		else if (cmd.redirections[i].type == 4)
			ft_printf("Type: <<, ");
		ft_printf("File: %s\n", cmd.redirections[i].file);
		i++;
	}
}
