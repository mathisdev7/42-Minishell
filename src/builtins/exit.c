/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 02:48:26 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/17 02:48:26 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exec_exit(t_cmd cmd)
{
	int	exit_code;

	if (!cmd.args[1])
	{
		rl_clear_history();
		//printf("\033[1;32mBye! 👋\033[0m\n");
		exit(0);
	}
	if (!is_numeric(cmd.args[1]))
	{
		fprintf(stderr, "minishell: exit: %s: numeric argument required\n",
			cmd.args[1]);
		rl_clear_history();
		exit(255);
	}
	if (cmd.args[2])
		return (printf("minishell: exit: too many arguments\n"));
	exit_code = ft_atoi(cmd.args[1]) & 255;
	rl_clear_history();
	//printf("\033[1;32mBye! 👋\033[0m\n");
	exit(exit_code);
}