/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 04:19:05 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/14 04:19:05 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		ft_putstr_fd(current->name, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(current->value, 1);
		ft_putchar_fd('\n', 1);
		current = current->next;
	}
}

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
		printf("[%s], ", cmd.args[i]);
		i++;
	}
	printf("\n");
}

void	print_redirections(t_cmd cmd)
{
	int	i;

	if (!cmd.redirections || cmd.nb_redirections == 0)
	{
		printf("No redirections\n");
		return;
	}
	for (i = 0; i < cmd.nb_redirections; i++)
	{
		printf("Redirection %d: ", i + 1);
		if (cmd.redirections[i].type == 1)
			printf("Type: >, ");
		else if (cmd.redirections[i].type == 2)
			printf("Type: >>, ");
		else if (cmd.redirections[i].type == 3)
			printf("Type: <, ");
		else if (cmd.redirections[i].type == 4)
			printf("Type: <<, ");
		printf("File: %s\n", cmd.redirections[i].file);
	}
}