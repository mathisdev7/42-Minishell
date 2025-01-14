/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:15:22 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 14:31:00 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_exit_status(t_env **envp, int *i)
{
	char	*var_value;

	var_value = ft_getenv("?", *envp);
	if (var_value)
		ft_printf("%s", var_value);
	(*i)++;
}

static void	handle_var_name(char *arg, int *i, char **var_name)
{
	int	k;

	k = 0;
	while (arg[*i + k] && (ft_isalnum(arg[*i + k]) || arg[*i + k] == '_'))
		k++;
	if (k == 0)
	{
		ft_printf("$");
		return ;
	}
	*var_name = ft_calloc(k + 1, sizeof(char));
	if (!*var_name)
		return ;
	ft_strncpy(*var_name, &arg[*i], k);
	(*var_name)[k] = '\0';
	*i += k;
}

void	print_env_var(char *arg, int *i, t_env **envp)
{
	char	*var_name;
	char	*var_value;

	if (!arg || !i || !envp || !*envp)
		return ;
	(*i)++;
	if (!arg[*i])
	{
		ft_printf("$");
		return ;
	}
	if (arg[*i] == '?')
	{
		print_exit_status(envp, i);
		return ;
	}
	var_name = NULL;
	handle_var_name(arg, i, &var_name);
	if (!var_name)
		return ;
	var_value = ft_getenv(var_name, *envp);
	if (var_value)
		ft_printf("%s", var_value);
	free(var_name);
}

void	print_regular_arg(char *arg, int *i, t_env **envp)
{
	(void)i;
	(void)envp;
	ft_printf("%s", arg);
}
