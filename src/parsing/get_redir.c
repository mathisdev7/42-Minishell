/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:44:11 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/20 13:44:16 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
