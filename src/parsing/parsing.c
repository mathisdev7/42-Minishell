/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 04:39:18 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/18 13:54:27 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_var_name(char *arg, int *j)
{
	int		k;
	char	*var_name;

	k = *j + 1;
	if (arg[k] == '?')
	{
		(*j) += 2;
		return (ft_strdup("?"));
	}
	while (arg[k] && (ft_isalnum(arg[k]) || arg[k] == '_'))
		k++;
	var_name = ft_substr(arg, *j + 1, k - (*j + 1));
	*j = k;
	return (var_name);
}

static void	replace_variable(char **arg, int j, char *var_name, t_env *envp)
{
	char	*var_value;
	char	*new_arg;

	var_value = ft_getenv(var_name, envp);
	if (!var_value)
		var_value = "";
	new_arg = replace_env_var(*arg, j, var_value, ft_strlen(var_name));
	if (new_arg)
	{
		free(*arg);
		*arg = new_arg;
	}
}

static void	process_arg(char **arg, t_env *envp)
{
	int		j;
	int		in_single_quote;
	char	*var_name;

	j = 0;
	in_single_quote = 0;
	while ((*arg)[j])
	{
		if ((*arg)[j] == '\'')
			in_single_quote = !in_single_quote;
		if (!in_single_quote && (*arg)[j] == '$' && (*arg)[j + 1])
		{
			var_name = get_var_name(*arg, &j);
			if (var_name)
			{
				replace_variable(arg, j - ft_strlen(var_name) - 1, var_name,
					envp);
				free(var_name);
			}
		}
		else
			j++;
	}
}

void	parse_env_vars(char **args, t_env *envp)
{
	int	i;

	i = 0;
	while (args[i])
	{
		process_arg(&args[i], envp);
		i++;
	}
}
