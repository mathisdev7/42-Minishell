/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:57:35 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/09 20:57:35 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void exec_pwd(void)
{
	char current_path[PATH_MAX];

    if (getcwd(current_path, sizeof(current_path)) != NULL)
        printf("[🧭] -> %s\n", current_path);
	else
        perror("Error retrieving the current directory");
}
