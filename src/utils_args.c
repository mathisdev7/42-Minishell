/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:00:47 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/18 11:21:39 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**allocate_args(int nb_args)
{
	char	**args;

	args = malloc(sizeof(char *) * (nb_args + 1));
	if (!args)
		return (NULL);
	args[nb_args] = NULL;
	return (args);
}

int	count_args(char *str)
{
	int	i;
	int	count;
	int	in_quotes;

	i = 0;
	count = 0;
	in_quotes = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ' && !in_quotes)
			i++;
		if (str[i])
		{
			count++;
			while (str[i] && ((str[i] != ' ' && !in_quotes) || in_quotes))
			{
				if (str[i] == '"')
					in_quotes = !in_quotes;
				i++;
			}
		}
	}
	return (count);
}

char	*extract_arg(char *str, int *i)
{
	int		start;
	int		len;
	int		in_quotes;
	char	*arg;

	len = 0;
	in_quotes = 0;
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	start = *i;
	while (str[*i] && ((str[*i] != ' ' && !in_quotes) || in_quotes))
	{
		if (str[*i] == '"')
			in_quotes = !in_quotes;
		(*i)++;
		len++;
	}
	arg = malloc(sizeof(char) * (len + 1));
	if (!arg)
		return (NULL);
	ft_strlcpy(arg, &str[start], len + 1);
	return (arg);
}

static int	handle_args(char **args, char *str, int nb_args)
{
	int	i;
	int	arg_index;

	i = 0;
	arg_index = 0;
	while (arg_index < nb_args)
	{
		args[arg_index] = extract_arg(str, &i);
		if (!args[arg_index])
		{
			while (--arg_index >= 0)
				free(args[arg_index]);
			free(args);
			return (0);
		}
		arg_index++;
	}
	return (1);
}

char	**ft_split_args(char *str)
{
	char	**args;
	int		nb_args;

	if (!str)
		return (NULL);
	nb_args = count_args(str);
	args = allocate_args(nb_args);
	if (!args)
		return (NULL);
	if (!handle_args(args, str, nb_args))
		return (NULL);
	return (args);
}
