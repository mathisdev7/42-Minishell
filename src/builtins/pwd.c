/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 23:17:03 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/16 23:17:03 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_pwd()
{
	char	current_path[1024];

	if (getcwd(current_path, sizeof(current_path)) != NULL)
		printf("%s\n", current_path);
	else
	{
		perror("Error retrieving the current directory");
		return (1);
	}
	return (0);
}