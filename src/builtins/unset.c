/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 00:45:59 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/17 00:45:59 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_env_var(char *var_name)
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

void	ft_env_remove_if(t_env **begin_list, char *data_ref, int (*cmp)(char *,
			char *))
{
	t_env	*cur;

	if (begin_list == NULL || *begin_list == NULL)
		return ;
	cur = *begin_list;
	if (cmp(cur->name, data_ref) == 0)
	{
		*begin_list = cur->next;
		free(cur->name);
		free(cur->value);
		free(cur);
		ft_env_remove_if(begin_list, data_ref, cmp);
	}
	else
		ft_env_remove_if(&cur->next, data_ref, cmp);
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