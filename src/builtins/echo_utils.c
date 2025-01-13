/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 00:15:00 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/13 16:06:15 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_quoted_with_single(char *str)
{
	return (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'');
}

void	print_without_quotes(char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != '\'')
	{
		printf("%c", str[i]);
		i++;
	}
}

void	print_env_var(char *arg, int *i, t_env **envp)
{
	int		k;
	char	*var_name;
	char	*var_value;

	(*i)++;
	k = 0;
	if (arg[*i] == '?')
	{
		var_value = ft_getenv("?", *envp);
		if (var_value)
			printf("%s", var_value);
		(*i)++;
		return;
	}

	while (arg[*i + k] && (ft_isalnum(arg[*i + k]) || arg[*i + k] == '_'))
		k++;

	if (k == 0)
	{
		printf("$");
		return;
	}

	var_name = malloc(sizeof(char) * (k + 1));
	ft_strncpy(var_name, &arg[*i], k);
	var_name[k] = '\0';

	var_value = ft_getenv(var_name, *envp);
	if (var_value)
		printf("%s", var_value);

	free(var_name);
	*i += k;
}

void	print_regular_arg(char *arg, int *i, t_env **envp)
{
	(void)i;
	(void)envp;
	printf("%s", arg);
}
