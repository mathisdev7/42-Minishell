/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 00:30:00 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/13 18:50:53 by mazeghou         ###   ########.fr       */
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
    int     start;
    int     in_single_quotes;

    if (!str)
        return (NULL);
    if (str[0] == '$' && str[1] == '?')
    {
        var_value = ft_getenv("?", envp);
        if (!var_value)
            return (ft_strdup("0"));
        return (ft_strdup(var_value));
    }
    result = malloc(sizeof(char) * (ft_strlen(str) * 2 + 1));
    if (!result)
        return (NULL);
    i = 0;
    j = 0;
    in_single_quotes = 0;

    while (str[i])
    {
        if (str[i] == '\'')
            in_single_quotes = !in_single_quotes;

        if (str[i] == '$' && !in_single_quotes && str[i + 1] &&
            (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
        {
            i++;
            start = i;
            while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
                i++;
            var_name = ft_substr(str, start, i - start);
            var_value = ft_getenv(var_name, envp);
            if (var_value)
            {
                ft_strcpy(&result[j], var_value);
                j += ft_strlen(var_value);
            }
            free(var_name);
            i--;
        }
        else
            result[j++] = str[i];
        i++;
    }
    result[j] = '\0';
    return (result);
}

