/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:56:29 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/09 14:56:29 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    init_shell()
{
    loop_shell();
}

void    handle_cmd(char *cmd_line)
{
    int i;
    char    **cmd;

    i = 0;
    cmd = ft_split(cmd_line, ' ');
    while (cmd[i])
    {
        printf("[%s] ", cmd[i]);
        i++;
    }
    printf("\n");
}

void    loop_shell()
{
    char	*line;

	while (1)
    {
	    line = readline("minishell>");
        if (ft_strncmp(line, "exit", ft_strlen(line)) == 0)
            return ;
        handle_cmd(line);
        
    }
}