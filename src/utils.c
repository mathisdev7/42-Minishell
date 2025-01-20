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

int	is_valid_var_char(char c, int first_char)
{
	if (first_char)
		return (ft_isalpha(c) || c == '_' || c == '?');
	return (ft_isalnum(c) || c == '_');
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

char	*get_cmd_path(char *cmd_name, char *path_var)
{
	int		i;
	char	**splitted_path;
	char	*full_cmd;

	i = 0;
	splitted_path = ft_split(path_var + 5, ':');
	if (!splitted_path)
		return (NULL);
	while (splitted_path[i])
	{
		if (access(cmd_name, X_OK) == 0)
			return (cmd_name);
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

void	update_status(t_env **envp, int status)
{
	t_env	*current;
	char	*status_str;

	current = *envp;
	status_str = ft_itoa(status & 255);
	while (current)
	{
		if (ft_strcmp(current->name, "?") == 0)
		{
			free(current->value);
			current->value = status_str;
			return ;
		}
		current = current->next;
	}
	current = malloc(sizeof(t_env));
	if (!current)
	{
		free(status_str);
		return ;
	}
	current->name = ft_strdup("?");
	current->value = status_str;
	current->next = *envp;
	*envp = current;
}
