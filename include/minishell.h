/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:29:29 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 14:44:16 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
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

typedef struct s_redirection
{
	char			*file;
	int				type;
	int				fd;
}					t_redirection;

typedef struct s_cmd
{
	char			**args;
	int				pipe_presence;
	t_redirection	*redirections;
	int				nb_redirections;
}					t_cmd;

typedef struct s_cmd_line
{
	t_cmd			*cmds;
	int				nb_cmds;
}					t_cmd_line;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_quote_state
{
	int				in_single;
	int				in_double;
	size_t			i;
	size_t			j;
}					t_quote_state;

typedef struct s_parsing_state
{
	int				i;
	int				cmd_index;
	int				in_quotes;
	char			quote_type;
	char			*cmd_start;
	t_cmd_line		*cmd_line;
	t_env			*envp;
}					t_parsing_state;

typedef struct s_expand
{
	char	*result;
	int		i;
	int		j;
	t_env	*envp;
}	t_expand;

void				init_shell(t_env **envp);
void				loop_shell(t_env **envp);

// path utils
char				*check_direct_path(char *cmd_name);
char				**get_splitted_path(t_env *envp);
char				*set_full_cmd(char *current_path, char *cmd_name);
char				*get_cmd_path(t_env *envp, char *cmd_name);

// cmd utils
void				free_cmd(t_cmd *cmd);
void				handle_cmd(char *cmd_line);
t_cmd				parse_cmd(char *cmd_line, t_env *envp);
int					exec_builtin(t_cmd cmd, t_env **envp);
int					cmd_exists(char *cmd, t_env *envp);
void				execute_command(t_cmd cmd, t_env **envp);
t_cmd_line			parse_cmd_line(char *line, t_env *envp);
t_redirection		*parse_redirection(char *cmd, int *nb_redirections);
char				**ft_split_args(char *str);

// process utils
int					process_input(char *line, t_env **envp);
void				setup_pipes(int *prev_pipe_fd, int *pipe_fd, int i,
						int nb_cmds);
void				manage_pipes(int *prev_pipe_fd, int *pipe_fd, int i,
						int nb_cmds);
int					handle_redirections(t_cmd *cmd);
int					init_pipeline(t_cmd_line *cmd_line, pid_t **pids);

// redirections utils
int					count_redirections(char *cmd);
t_redirection		*parse_redirection(char *cmd, int *nb_redirections);
char				*extract_file_name(char *cmd, int *i);
void				parse_here_doc(t_redirection *redirection, char *delimiter);
void				remove_redir_char(char *str);
int					handle_heredoc(t_redirection *redirections, int redir_index,
						char *cmd, int *i);
int					handle_append(t_redirection *redirections, int redir_index,
						char *cmd, int *i);
int					handle_simple_redir(t_redirection *redirections,
						int redir_index, char *cmd, int *i);
t_redirection		*init_redirections(int nb_redirections);

// env utils
void				update_status(t_env **envp, int status);
t_env				*init_env(char **envp);
void				free_env(t_env *env);
char				*ft_getenv(char *name, t_env *envp);
void				ft_env_remove_if(t_env **begin_list, char *data_ref,
						int (*cmp)(char *, char *));
char				**env_to_array(t_env *envp);
char				*expand_env_var(char *str, t_env *envp);
int					is_empty_cmd(char *cmd_line);

// ft utils
char				*ft_strjoin3(char *s1, char *s2, char *s3);
char				*ft_strncpy(char *dest, char *src, unsigned int n);
char				*ft_strcpy(char *dest, char *src);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strstr(char *str, char *to_find);
char				*ft_strtok(char *str, char sepa);

// builtins
int					exec_builtin(t_cmd cmd, t_env **envp);
int					exec_cmd(t_cmd cmd, t_env **envp);
int					exec_echo(t_cmd cmd, t_env **envp);
int					exec_cd(t_cmd cmd, t_env **envp);
int					exec_pwd(t_cmd cmd);
int					exec_unset(t_cmd cmd, t_env **envp);
int					exec_export(t_cmd cmd, t_env **envp);
int					exec_env(t_cmd cmd, t_env **envp);
int					exec_exit(t_cmd cmd, t_env **envp);

// builtins utils
void				print_regular_arg(char *arg, int *i, t_env **envp);
int					exec_exit(t_cmd cmd, t_env **envp);
int					is_builtin_cmd(char **cmd_args);
int					execute_pipeline(t_cmd_line *cmd_line, t_env **envp,
						pid_t *pids);
int					handle_export_arg(char *arg, t_env **env_list);
int					is_valid_identifier(char *str);
void				add_env_var(t_env **env_list, char *key, char *value);

// printf
int					ft_printf(const char *format, ...);

// signals utils
void				setup_signals(void);

// parser utils
void				skip_spaces(char **str);
void				handle_quotes(char c, int *in_quotes, char *quote_type);
void				process_pipe(t_parsing_state *state, char *line);
void				process_final_command(t_parsing_state *state, char *line);
int					handle_empty_line(char *line);
char				*remove_quotes(char *str);
char				*extract_arg(char *str, int *i);
void				handle_quotes(char c, int *in_quotes, char *quote_type);
int					count_args(char *str);

#endif
