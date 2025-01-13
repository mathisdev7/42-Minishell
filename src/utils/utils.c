/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:45:00 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/13 15:28:10 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int count_args(char *str)
{
    int count = 0;
    int i = 0;
    int in_quotes = 0;
    char quote_type = 0;

    while (str && str[i])
    {
        while (str[i] && !in_quotes && (str[i] == ' ' || str[i] == '\t'))
            i++;
        if (str[i])
            count++;
        while (str[i] && (in_quotes || (str[i] != ' ' && str[i] != '\t')))
        {
            if ((str[i] == '"' || str[i] == '\'') && (!in_quotes || str[i] == quote_type))
            {
                in_quotes = !in_quotes;
                quote_type = in_quotes ? str[i] : 0;
            }
            i++;
        }
    }
    return count;
}

char *extract_arg(char *str, int *i)
{
    int start = *i;
    int len = 0;
    int in_quotes = 0;
    char quote_type = 0;
    char *arg;

    while (str[*i] && (in_quotes || (str[*i] != ' ' && str[*i] != '\t')))
    {
        if ((str[*i] == '"' || str[*i] == '\'') && (!in_quotes || str[*i] == quote_type))
        {
            in_quotes = !in_quotes;
            quote_type = in_quotes ? str[*i] : 0;
        }
        (*i)++;
        len++;
    }

    arg = malloc(sizeof(char) * (len + 1));
    if (!arg)
        return NULL;

    strncpy(arg, &str[start], len);
    arg[len] = '\0';
    return arg;
}

char **ft_split_args(char *str)
{
    int count = count_args(str);
    char **args = malloc(sizeof(char *) * (count + 1));
    if (!args)
        return NULL;

    int i = 0;
    int arg_index = 0;

    while (str[i])
    {
        while (str[i] && (str[i] == ' ' || str[i] == '\t'))
            i++;
        if (str[i])
        {
            args[arg_index] = extract_arg(str, &i);
            if (!args[arg_index])
            {
                while (arg_index > 0)
                    free(args[--arg_index]);
                free(args);
                return NULL;
            }
            arg_index++;
        }
    }
    args[arg_index] = NULL;
    return args;
}
