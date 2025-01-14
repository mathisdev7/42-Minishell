/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:15:22 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 14:26:31 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_expanded_len(char *str, t_env *envp)
{
	int		len;
	t_env	*current;

	len = ft_strlen(str);
	current = envp;
	while (current)
	{
		if (ft_strstr(str, current->name))
			len += ft_strlen(current->value);
		current = current->next;
	}
	return (len);
}

static void	handle_exit_status(t_expand *exp)
{
	char	*var_value;

	var_value = ft_getenv("?", exp->envp);
	if (var_value)
	{
		ft_strlcpy(exp->result + exp->j, var_value, ft_strlen(var_value) + 1);
		exp->j += ft_strlen(var_value);
	}
}

static void	handle_env_var(char *str, t_expand *exp)
{
	char	*var_name;
	char	*var_value;
	int		start;

	start = exp->i;
	while (str[exp->i] && (ft_isalnum(str[exp->i]) || str[exp->i] == '_'))
		exp->i++;
	var_name = ft_substr(str, start, exp->i - start);
	if (!var_name)
		return ;
	var_value = ft_getenv(var_name, exp->envp);
	free(var_name);
	if (var_value)
	{
		ft_strlcpy(exp->result + exp->j, var_value, ft_strlen(var_value) + 1);
		exp->j += ft_strlen(var_value);
	}
}

static void	process_dollar(char *str, t_expand *exp)
{
	exp->i++;
	if (str[exp->i] == '?')
	{
		handle_exit_status(exp);
		exp->i++;
	}
	else
		handle_env_var(str, exp);
}

char	*expand_env_var(char *str, t_env *envp)
{
	t_expand	exp;
	int			in_single_quotes;

	if (!str)
		return (ft_strdup(""));
	exp.result = ft_calloc(get_expanded_len(str, envp) + 1, sizeof(char));
	if (!exp.result)
		return (ft_strdup(str));
	exp.i = 0;
	exp.j = 0;
	exp.envp = envp;
	in_single_quotes = 0;
	while (str[exp.i])
	{
		if (str[exp.i] == '\'')
			in_single_quotes = !in_single_quotes;
		if (str[exp.i] == '$' && !in_single_quotes && str[exp.i + 1])
			process_dollar(str, &exp);
		else
			exp.result[exp.j++] = str[exp.i++];
	}
	return (exp.result);
}
