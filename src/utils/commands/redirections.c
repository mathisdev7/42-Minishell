/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:25:22 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 14:07:46 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_redirections(char *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if ((cmd[i] == '>' && cmd[i + 1] == '>') || (cmd[i] == '<' && cmd[i
					+ 1] == '<'))
		{
			count++;
			i += 2;
		}
		else if (cmd[i] == '>' || cmd[i] == '<')
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}
