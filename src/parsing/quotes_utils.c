/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 00:30:00 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/13 19:52:29 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*result;
	int		in_quotes;
	char	quote_type;

	if (!str)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_quotes = 0;
	quote_type = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && (!in_quotes || str[i] == quote_type))
		{
			in_quotes = !in_quotes;
			quote_type = in_quotes ? str[i] : 0;
		}
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

char *expand_env_var(char *str, t_env *envp)
{
    char    *result;
    char    *var_name;
    char    *var_value;
    int     i;
    int     j;
    int     len;
    int     in_single_quotes;

    if (!str)
        return (ft_strdup(""));

    len = ft_strlen(str);
    t_env *current = envp;
    while (current)
    {
        if (strstr(str, current->name))
            len += ft_strlen(current->value);
        current = current->next;
    }

    result = ft_calloc(len + 1, sizeof(char));
    if (!result)
        return (ft_strdup(str));

    i = 0;
    j = 0;
    in_single_quotes = 0;

    while (str[i])
    {
        if (str[i] == '\'')
        {
            in_single_quotes = !in_single_quotes;
            result[j++] = str[i++];
        }
        else if (str[i] == '$' && !in_single_quotes && str[i + 1])
        {
            i++;
            if (str[i] == '?')
            {
                var_value = ft_getenv("?", envp);
                if (var_value)
                {
                    ft_strlcpy(result + j, var_value, len - j);
                    j += ft_strlen(var_value);
                }
                i++;
                continue;
            }

            int start = i;
            while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
                i++;

            if (start == i)
            {
                result[j++] = '$';
                continue;
            }

            var_name = ft_substr(str, start, i - start);
            if (!var_name)
                continue;

            var_value = ft_getenv(var_name, envp);
            free(var_name);

            if (var_value)
            {
                ft_strlcpy(result + j, var_value, len - j + 1);
                j += ft_strlen(var_value);
            }
        }
        else
            result[j++] = str[i++];
    }

    result[j] = '\0';
    return result;
}

