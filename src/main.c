/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:27:07 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/09 14:27:07 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
 	t_history *history = NULL;

    add_history(&history, "ls -la");
    add_history(&history, "cd /");
    add_history(&history, "echo Hello, World!");

    printf("Historique des commandes :\n");
    print_history(history);

    free_history(&history);
	return (0);
}
