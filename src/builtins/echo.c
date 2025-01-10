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

void    print_env_var(char *arg, int *i, t_env **envp)
{
    int        k;
    char    *var_name;
    char    *var_value;

    k = 0;
    *i += 1;
    while (ft_isalpha(arg[*i + k])
        || ft_isalnum(arg[*i + k]) || arg[*i + k] == '_')
        k++;
    var_name = malloc(sizeof(char) * (k + 1));
    ft_strncpy(var_name, &arg[*i], k);
    var_name[k] = '\0';
    var_value = ft_getenv(var_name, *envp);
    if (var_value)
        printf("%s", var_value);
    free(var_name);
    *i += k;
}

void    print_args(int j, int new_line, t_cmd cmd, t_env **envp)
{
    int    i;

    i = 0;
    while (cmd.args[j])
    {
        i = 0;
        while (cmd.args[j][i])
        {
            if (cmd.args[j][i] == '$' && (ft_isalpha(cmd.args[j][i + 1])
                    || cmd.args[j][i + 1] == '_'))
            {
                print_env_var(cmd.args[j], &i, envp);
            }
            else
            {
                printf("%c", cmd.args[j][i]);
                i++;
            }
        }
        if (cmd.args[j + 1])
            printf(" ");
        j++;
    }
    if (new_line)
        printf("\n");
}

void    exec_echo(t_cmd cmd, t_env **envp)
{
    int    j;
    int    new_line;

    j = 1;
    new_line = 1;
    if (cmd.args[1] == NULL)
    {
        printf("\n");
        return ;
    }
    if (ft_strcmp(cmd.args[1], "-n") == 0)
    {
        new_line = 0;
        j++;
    }
    print_args(j, new_line, cmd, envp);
}
