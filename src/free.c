/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 04:13:50 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/14 04:13:50 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_env(t_env *env)
{
    t_env *tmp;

    while (env)
    {
        tmp = env;
        free(env->name);
        free(env->value);
        env = env->next;
        free(tmp);
    }
}


void	free_shell(t_shell *shell)
{
	free_env(shell->env);
	free(shell);
}