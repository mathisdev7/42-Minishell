/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:40:27 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/12 01:37:41 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_env(t_cmd cmd, t_env **envp)
{
	t_env	*current;

	(void)cmd;
	if (!envp || !*envp)
	{
		ft_printf("Error: Environment not initialized\n");
		return (1);
	}
	current = *envp;
	while (current)
	{
		ft_printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	return (0);
}
