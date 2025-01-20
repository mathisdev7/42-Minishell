/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 04:39:18 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/20 11:19:10 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parse_env_vars(char **args, t_env *envp)
{
	int		i;
	int		j;
	int		k;
	char	*var_name;
	char	*var_value;
	char	*new_arg;
	int		in_single_quote;

	i = 0;
	while (args[i])
	{
		j = 0;
		in_single_quote = 0;
		while (args[i][j])
		{
			if (args[i][j] == '\'')
				in_single_quote = !in_single_quote;
			if (!in_single_quote && args[i][j] == '$' && args[i][j + 1])
			{
				k = j + 1;
				if (args[i][k] == '?')
				{
					k++;
					var_name = ft_strdup("?");
				}
				else
				{
					while (args[i][k] && (ft_isalnum(args[i][k])
							|| args[i][k] == '_'))
						k++;
					var_name = ft_substr(args[i], j + 1, k - (j + 1));
				}
				if (var_name)
				{
					var_value = ft_getenv(var_name, envp);
					if (var_value)
					{
						new_arg = replace_env_var(args[i], j, var_value, k - (j
									+ 1));
						if (new_arg)
						{
							free(args[i]);
							args[i] = new_arg;
							j += ft_strlen(var_value) - 1;
						}
					}
					else
					{
						new_arg = replace_env_var(args[i], j, "", k - (j + 1));
						if (new_arg)
						{
							free(args[i]);
							args[i] = new_arg;
							j--;
						}
					}
					free(var_name);
				}
			}
			j++;
		}
		i++;
	}
}

char	*get_redir_file(char *cmd_line, int start)
{
	int		len;
	int		i;
	char	*file;

	len = 0;
	i = start;
	while (cmd_line[i] && (cmd_line[i] == ' ' || cmd_line[i] == '\t'))
		i++;
	start = i;
	while (cmd_line[i] && cmd_line[i] != ' ' && cmd_line[i] != '\t'
		&& cmd_line[i] != '>' && cmd_line[i] != '<' && cmd_line[i] != '|')
	{
		len++;
		i++;
	}
	file = malloc(len + 1);
	if (!file)
		return (NULL);
	i = -1;
	while (++i < len)
		file[i] = cmd_line[start + i];
	file[i] = '\0';
	return (file);
}

t_cmd	parse_cmd(char *cmd_line, t_env *envp, int pipe_presence)
{
	char	**args;
	t_cmd	cmd;
	char	*cleaned_line;
	char	*tmp_cmd_line;

	cmd.nb_redirections = count_redirections(cmd_line);
	cmd.redirections = NULL;
	cmd.args = NULL;
	if (cmd.nb_redirections > 0)
	{
		cmd.redirections = malloc(sizeof(t_redirection) * cmd.nb_redirections);
		if (!cmd.redirections)
			return (cmd);
		parse_redirections(&cmd, cmd_line);
		tmp_cmd_line = remove_redirections(cmd_line);
		if (!tmp_cmd_line)
		{
			free(cmd.redirections);
			return (cmd);
		}
		cmd_line = tmp_cmd_line;
	}
	cleaned_line = remove_out_spaces(cmd_line);
	if (cmd.nb_redirections > 0)
		free(tmp_cmd_line);
	if (!cleaned_line)
	{
		if (cmd.redirections)
			free(cmd.redirections);
		return (cmd);
	}
	args = ft_split_args(cleaned_line);
	free(cleaned_line);
	parse_env_vars(args, envp);
	if (!args)
	{
		if (cmd.redirections)
			free(cmd.redirections);
		return (cmd);
	}
	cmd.args = remove_out_quotes(args);
	free_strs(args);
	cmd.pipe_presence = pipe_presence;
	return (cmd);
}

int	is_only_spaces(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (0);
		str++;
	}
	return (1);
}

t_cmd_line	parse_cmd_line(char *line, t_env *envp)
{
	int			i;
	t_cmd_line	cmd_line;
	char		**splitted_cmds;

	i = 0;
	cmd_line.cmds = NULL;
	cmd_line.nb_cmds = 0;
	if (!line || !*line)
		return (cmd_line);
	if (!are_quotes_close(line, '\'') || !are_quotes_close(line, '"'))
	{
		printf("minishell: Unclosed quotes detected\n");
		return (cmd_line);
	}
	if (is_only_spaces(line))
		return (cmd_line);
	splitted_cmds = ft_split(line, '|');
	if (!splitted_cmds)
	{
		printf("minishell: %s not found", line);
		free_strs(splitted_cmds);
		return (cmd_line);
	}
	cmd_line.nb_cmds = 0;
	while (splitted_cmds[cmd_line.nb_cmds])
		cmd_line.nb_cmds++;
	cmd_line.cmds = malloc(sizeof(t_cmd) * (cmd_line.nb_cmds + 1));
	if (!cmd_line.cmds)
	{
		free_strs(splitted_cmds);
		return (cmd_line);
	}
	while (splitted_cmds[i])
	{
		if (i < cmd_line.nb_cmds - 1)
			cmd_line.cmds[i] = parse_cmd(splitted_cmds[i], envp, 1);
		else
			cmd_line.cmds[i] = parse_cmd(splitted_cmds[i], envp, 0);
		i++;
	}
	free_strs(splitted_cmds);
	return (cmd_line);
}

char	*remove_redirections(char *cmd_line)
{
	int		i;
	int		j;
	int		in_single_quote;
	int		in_double_quote;
	char	*new_cmd_line;

	i = 0;
	j = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	new_cmd_line = malloc(ft_strlen(cmd_line) + 1);
	if (!new_cmd_line)
		return (NULL);
	while (cmd_line[i])
	{
		if (cmd_line[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (cmd_line[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		if (!in_single_quote && !in_double_quote && (cmd_line[i] == '>'
				|| cmd_line[i] == '<'))
		{
			if (cmd_line[i + 1] == '>' || cmd_line[i + 1] == '<')
				i++;
			i++;
			while (cmd_line[i] && (cmd_line[i] == ' ' || cmd_line[i] == '\t'))
				i++;
			while (cmd_line[i] && cmd_line[i] != ' ' && cmd_line[i] != '\t'
				&& cmd_line[i] != '>' && cmd_line[i] != '<')
				i++;
		}
		else
		{
			new_cmd_line[j++] = cmd_line[i++];
		}
	}
	new_cmd_line[j] = '\0';
	return (new_cmd_line);
}
