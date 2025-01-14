/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:45:22 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 13:52:05 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_args(char **args, int arg_index)
{
	while (arg_index > 0)
		free(args[--arg_index]);
	free(args);
}

static int	process_arg(char **args, int *arg_index, char *str, int *i)
{
	args[*arg_index] = extract_arg(str, i);
	if (!args[*arg_index])
	{
		free_args(args, *arg_index);
		return (0);
	}
	(*arg_index)++;
	return (1);
}

char	**ft_split_args(char *str)
{
	char	**args;
	int		i;
	int		arg_index;

	args = malloc(sizeof(char *) * (count_args(str) + 1));
	if (!args)
		return (NULL);
	i = 0;
	arg_index = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i] && !process_arg(args, &arg_index, str, &i))
			return (NULL);
	}
	args[arg_index] = NULL;
	return (args);
}
