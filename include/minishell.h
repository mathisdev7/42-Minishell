/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:29:29 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/09 16:41:37 by nopareti         ###   ########.fr       */
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

typedef struct s_cmd
{
	char	*name;
	char	**args;
}	t_cmd;


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
t_cmd	parse_cmd(char *cmd_line);
int		count_cmd(char *str);
void    free_split(char **splitted);
int	ft_strcmp(char *s1, char *s2);

#endif
