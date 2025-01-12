/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:46:55 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/12 01:39:36 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_valid_env_var(char *var_name)
{
	int	i;

	if (!var_name || !*var_name)
		return (0);
	if (var_name[0] != '_' && !ft_isalpha(var_name[0]))
		return (0);
	i = 1;
	while (var_name[i])
	{
		if (!ft_isalpha(var_name[i]) && !ft_isalnum(var_name[i])
			&& var_name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	exec_unset(t_cmd cmd, t_env **envp)
{
	int	status;

	status = 0;
	if (!cmd.args[1])
		return (0);
	cmd.args++;
	while (*cmd.args)
	{
		if (!is_valid_env_var(*cmd.args))
		{
			printf("unset: `%s': not a valid identifier\n", *cmd.args);
			status = 1;
		}
		else
			ft_env_remove_if(envp, *cmd.args, ft_strcmp);
		cmd.args++;
	}
	return (status);
}
