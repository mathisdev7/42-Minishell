/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:22:32 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/11 23:40:22 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_quotes(char *cmd_line, int *i, char *quote, int *in_quote)
{
	if (cmd_line[*i] == '"' || cmd_line[*i] == '\'')
	{
		if (!*in_quote)
		{
			*quote = cmd_line[*i];
			*in_quote = 1;
		}
		else if (cmd_line[*i] == *quote)
			*in_quote = 0;
	}
	return ((*i)++);
}

static char	*allocate_and_copy_arg(char *cmd_line, int start, int end)
{
	char	*arg;

	arg = malloc(sizeof(char) * (end - start + 1));
	if (!arg)
		return (NULL);
	ft_strncpy(arg, &cmd_line[start], end - start);
	return (arg);
}

static int	process_argument(char *cmd_line, int *i, char **arg)
{
	int		start;
	char	quote;
	int		in_quote;

	while (cmd_line[*i] && (cmd_line[*i] == ' ' || cmd_line[*i] == '\t'))
		(*i)++;
	start = *i;
	in_quote = 0;
	while (cmd_line[*i] && (in_quote || (cmd_line[*i] != ' '
				&& cmd_line[*i] != '\t')))
		handle_quotes(cmd_line, i, &quote, &in_quote);
	*arg = allocate_and_copy_arg(cmd_line, start, *i);
	return (*arg != NULL);
}

char	**ft_split_args(char *cmd_line)
{
	char	**args;
	int		i;
	int		j;
	int		arg_count;

	if (!cmd_line)
		return (NULL);
	arg_count = count_args(cmd_line) + 1;
	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd_line[i] && j < arg_count)
	{
		if (!process_argument(cmd_line, &i, &args[j]))
		{
			free_split(args);
			return (NULL);
		}
		j++;
	}
	args[j] = NULL;
	return (args);
}

int	count_args(char *str)
{
	int		count;
	int		in_word;
	char	*ptr;

	count = 0;
	in_word = 0;
	ptr = str;
	while (*ptr)
	{
		if (*ptr != ' ' && *ptr != '\t')
		{
			if (!in_word)
			{
				count++;
				in_word = 1;
			}
		}
		else
			in_word = 0;
		ptr++;
	}
	return (count - 1);
}
