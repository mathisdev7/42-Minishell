/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:44:21 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/09 20:44:21 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    exec_cmd(t_cmd cmd)
{
    if (ft_strcmp(cmd.name, "cd") == 0)
    {
        if (cmd.args == NULL || cmd.args[0] == 0)
            exec_cd("none");
        else
            exec_cd(cmd.args[0]);
    }
	else if (ft_strcmp(cmd.name, "echo") == 0)
		exec_echo(cmd);
}