/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:29:45 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 12:29:49 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin_cmd(char **cmd_args)
{
	if (ft_strcmp(cmd_args[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd_args[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd_args[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd_args[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd_args[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd_args[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd_args[0], "exit") == 0)
		return (1);
	return (0);
}
