/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:29:29 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/09 15:54:43 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <signal.h>
#include <termios.h>
#include <curses.h>
#include <term.h>
#include <stdio.h>
#include "libft/libft.h"
#include <readline/readline.h>

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_history
{
    char *command;
    struct s_history *next;
} t_history;

void add_history(t_history **history, char *s);
void print_history(t_history *history);
void free_history(t_history **history);

void    init_shell(t_history *history);
void    loop_shell(t_history *history);

#endif
