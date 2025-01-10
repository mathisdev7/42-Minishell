/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:46:55 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/10 20:46:55 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void    exec_unset(t_cmd cmd, t_env **envp)
{
    cmd.args++;
    while (*cmd.args)
    {
        ft_env_remove_if(envp, *cmd.args, ft_strcmp);
        cmd.args++;
    }
}
