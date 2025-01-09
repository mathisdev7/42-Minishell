/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:56:58 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/09 19:56:58 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exec_echo(t_cmd cmd)
{
	int	new_line;

	new_line = 1;
    if (cmd.args[0] == NULL)
    {
        printf("\n");
        return;
    }
    if (ft_strcmp(cmd.args[0], "-n") == 0)
    {
        new_line = 0;
        cmd.args++;
    }
    while (*cmd.args)
    {
        if (**cmd.args == '$')
        {
			if (ft_strlen(*cmd.args) == 1)
				printf("$");
			else
			{
            	char *var_name = *cmd.args + 1;
            	char *value = getenv(var_name);
            	if (value)
                	printf("%s", value);
			}
        }
        else
        {
            printf("%s", *cmd.args);
        }
        if (*(cmd.args + 1))
            printf(" ");
        cmd.args++;
    }
    if (new_line)
        printf("\n");
}
