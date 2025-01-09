/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:29:29 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/09 15:08:50 by nopareti         ###   ########.fr       */
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

void    init_shell();
void    loop_shell();

#endif
