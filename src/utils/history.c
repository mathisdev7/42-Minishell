/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:47:57 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/09 14:47:57 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void add_history(t_history **history, char *s)
{
	t_history *new_entry;
	t_history *current;

    if (!s || !*s)
        return;
    new_entry = malloc(sizeof(t_history));
    if (!new_entry)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    new_entry->command = strdup(s);
    if (!new_entry->command)
    {
        perror("strdup");
        free(new_entry);
        exit(EXIT_FAILURE);
    }
    new_entry->next = NULL;
    if (!*history)
        *history = new_entry;
    else
    {
        current = *history;
        while (current->next)
            current = current->next;
        current->next = new_entry;
    }
}

void print_history(t_history *history)
{
    t_history *current = history;
    int index = 1;

    while (current)
    {
        printf("%d: %s\n", index++, current->command);
        current = current->next;
    }
}

void free_history(t_history **history)
{
    t_history *current = *history;
    t_history *next;

    while (current)
    {
        next = current->next;
        free(current->command);
        free(current);
        current = next;
    }
    *history = NULL;
}
