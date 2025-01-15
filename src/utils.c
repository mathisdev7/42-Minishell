/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 04:17:53 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/14 04:17:53 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

	while (str[*i] && str[*i] == ' ')
		(*i)++;
	start = *i;
	len = 0;
	in_quotes = 0;
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

char	**ft_split_args(char *str)
{
	char	**args;
	int		nb_args;
	int		i;
	int		arg_index;

	if (!str)
		return (NULL);
	nb_args = count_args(str);
	args = malloc(sizeof(char *) * (nb_args + 1));
	if (!args)
		return (NULL);
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
			return (NULL);
		}
		arg_index++;
	}
	args[nb_args] = NULL;
	return (args);
}

char	*remove_out_spaces(char *str)
{
	int		i;
	int		start;
	int		end;
	char	*new_str;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	start = i;
	if (!str[i])
		return (ft_strdup(""));
	end = ft_strlen(str) - 1;
	while (end > start && (str[end] == ' ' || str[end] == '\t'))
		end--;
	new_str = malloc(sizeof(char) * (end - start + 2));
	if (!new_str)
		return (NULL);
	i = 0;
	while (start <= end)
		new_str[i++] = str[start++];
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_getenv(char *name, t_env *envp)
{
	t_env	*current;

	if (!name || !envp)
		return (NULL);
	current = envp;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	is_valid_var_char(char c, int first_char)
{
	if (first_char)
		return (ft_isalpha(c) || c == '_' || c == '?');
	return (ft_isalnum(c) || c == '_');
}

char	*replace_env_var(char *arg, int start, char *value, int var_len)
{
	char	*new_arg;
	int		new_len;
	
	if (!value)
		value = "";
	new_len = ft_strlen(arg) - (var_len + 1) + ft_strlen(value) + 1;
	new_arg = malloc(sizeof(char) * new_len);
	if (!new_arg)
		return (NULL);
	ft_strlcpy(new_arg, arg, start + 1);
	ft_strlcat(new_arg, value, new_len);
	ft_strlcat(new_arg, arg + start + var_len + 1, new_len);
	return (new_arg);
}

char	*set_full_cmd(char *current_path, char *cmd_name)
{
	char	*full_cmd;
	char	*cmd_path;
	char	slash[2];

	slash[0] = '/';
	slash[1] = '\0';
	cmd_path = ft_strjoin(current_path, slash);
	full_cmd = ft_strjoin(cmd_path, cmd_name);
	free(cmd_path);
	return (full_cmd);
}

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	**env_to_array(t_env *env)
{
	t_env	*current;
	char	**env_array;
	int		size;
	int		i;
	char	*tmp;

	size = 0;
	current = env;
	while (current)
	{
		size++;
		current = current->next;
	}
	env_array = malloc(sizeof(char *) * (size + 1));
	if (!env_array)
		return (NULL);
	current = env;
	i = 0;
	while (current)
	{
		tmp = ft_strjoin(current->name, "=");
		env_array[i] = ft_strjoin(tmp, current->value);
		free(tmp);
		if (!env_array[i])
		{
			free_strs(env_array);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

char	*get_cmd_path(char *cmd_name, char *path_var)
{
	int	i;
	char	**splitted_path;
	char	*full_cmd;

	i = 0;
	splitted_path = ft_split(path_var + 5, ':');
	if (!splitted_path)
		return (NULL);
	while (splitted_path[i])
	{
		full_cmd = set_full_cmd(splitted_path[i], cmd_name);
		if (access(full_cmd, X_OK) == 0)
		{
			free_strs(splitted_path);
			return (full_cmd);
		}
		free(full_cmd);
		i++;
	}
	free_strs(splitted_path);
	return (NULL);
}