/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:29:29 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/09 20:46:15 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define HISTORY_FILE_PATH ".minishell_history"

# include "libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_cmd
{
	char	*name;
	char	**args;
}	t_cmd;


void    init_shell(void);
void    loop_shell(void);
void	handle_cmd(char *cmd_line);
t_cmd	parse_cmd(char *cmd_line);
int		count_args(char *str);
void    free_split(char **splitted);
int		ft_strcmp(char *s1, char *s2);
void	exec_cmd(t_cmd cmd);
void	exec_echo(t_cmd cmd);

#endif
