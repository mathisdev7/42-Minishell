/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:00:57 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/18 11:00:58 by mazeghou         ###   ########.fr       */
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
