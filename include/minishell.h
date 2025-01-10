/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:29:29 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/10 14:31:37 by mazeghou         ###   ########.fr       */
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
}			t_cmd;

typedef	struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

void    init_shell(t_env **envp);
void    loop_shell(t_env **envp);
void	handle_cmd(char *cmd_line);
t_cmd	parse_cmd(char *cmd_line, t_env **envp);
int		count_args(char *str);
void    free_split(char **splitted);
int		ft_strcmp(char *s1, char *s2);
char	*remove_quotes(char *arg);
void	exec_cmd(t_cmd cmd, t_env **envp);
void	exec_echo(t_cmd cmd);
int		exec_cd(char *path);
void	exec_pwd(void);
int	exec_export(t_cmd cmd, t_env **envp);
t_env	*init_env(char **envp);
void	free_env(t_env *env);

#endif
