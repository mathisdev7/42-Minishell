/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:29:29 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/12 20:32:26 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
#include <fcntl.h>

typedef struct s_redirection
{
    char *file;
    int type;
    int fd;
}               t_redirection;

typedef struct s_cmd
{
    char            **args;
    int             pipe_presence;
    t_redirection   *redirections;
    int             nb_redirections;
}               t_cmd;



typedef struct s_cmd_line
{
	t_cmd	*cmds;
	int		nb_cmds;
}					t_cmd_line;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_quote_state
{
	int		in_single;
	int		in_double;
	size_t	i;
	size_t	j;
}	t_quote_state;

void				init_shell(t_env **envp);
void				loop_shell(t_env **envp);

void				handle_cmd(char *cmd_line);
t_cmd				parse_cmd(char *cmd_line);

int					count_args(char *str);
void				free_split(char **splitted);
int					ft_strcmp(char *s1, char *s2);
char				*remove_quotes(char *arg);

int					exec_builtin(t_cmd cmd, t_env **envp);
int					exec_cmd(t_cmd cmd, t_env **envp);
int					exec_echo(t_cmd cmd, t_env **envp);
int					exec_cd(t_cmd cmd, t_env **envp);
int					exec_pwd(t_cmd cmd);
int					exec_unset(t_cmd cmd, t_env **envp);
int					exec_export(t_cmd cmd, t_env **envp);
int					exec_env(t_cmd cmd, t_env **envp);
int					exec_exit(t_cmd cmd, t_env **envp);

char				*ft_strncpy(char *dest, char *src, unsigned int n);
size_t				ft_strcspn(const char *s, const char *reject);
t_env				*init_env(char **envp);
void				free_env(t_env *env);
char				*ft_getenv(char *name, t_env *envp);
int					is_builtin_cmd(char **cmd_args);
void				ft_env_remove_if(t_env **begin_list, char *data_ref,
						int (*cmp)(char *, char *));
char				*get_cmd_path(t_env *envp, char *cmd_name);
char				**get_splitted_path(t_env *envp);
char				*set_full_cmd(char *current_path, char *cmd_name);

char				**ft_split_args(char *cmd_line);

void				update_status(t_env **envp, int status);

char				**env_to_array(t_env *envp);

char				*ft_strjoin3(char *s1, char *s2, char *s3);
char				*ft_strcpy(char *dest, char *src);

void				setup_signals(void);

t_cmd_line parse_cmd_line(char	*line);
int				exec_pipe_cmd(t_cmd_line cmd_line, t_env **envp);

int				cmd_exists(char *cmd, t_env *envp);
int				process_input(char *line, t_env **envp);
int					is_quoted_with_single(char *str);
void				print_without_quotes(char *str);
void				print_regular_arg(char *arg, int *i, t_env **envp);
void				print_env_var(char *arg, int *i, t_env **envp);
t_redirection *parse_redirection(char **cmd_args, int *nb_redirections);

#endif
