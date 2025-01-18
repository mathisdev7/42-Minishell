/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 03:47:03 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/18 15:21:02 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "structures.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>

/*----------------------- INIT.C ---------------------------*/
t_shell		*init_shell(char **envp);
t_env		*init_env(char **envp);
void		prompt_system(t_shell *shell);
void		setup_signals(void);
/*----------------------- INIT.C ---------------------------*/

/*----------------------- FREE.C ---------------------------*/
void		free_shell(t_shell *shell);
/*----------------------- FREE.C ---------------------------*/

/*----------------------- DEBUG.C ---------------------------*/
void		print_cmd_args(t_cmd cmd);
void		print_redirections(t_cmd cmd);
/*----------------------- DEBUG.C ---------------------------*/

/*----------------------- PARSING.C ---------------------------*/
t_cmd_line	parse_cmd_line(char *line, t_env *envp);
t_cmd		parse_cmd(char *cmd_line, t_env *envp, int pipe_presence);
void		parse_env_vars(char **args, t_env *envp);
char		*remove_redirections(char *cmd_line);
void		handle_redirection(t_cmd *cmd, char *cmd_line, int *i,
				int *redir_index);
void		toggle_quote_redir(char c, int *in_single_quote,
				int *in_double_quote);
int			count_redirections_in_line(char *cmd_line);
void		update_quote_state_redir(char c, int *in_single_quote,
				int *in_double_quote);
int			skip_redirection_target(const char *cmd_line, int i);
void		parse_redirections(t_cmd *cmd, char *cmd_line);
/*----------------------- PARSING.C ---------------------------*/

/*----------------------- UTILS.C ---------------------------*/
char		**ft_split_args(char *str);
char		*remove_out_spaces(char *str);
char		**remove_out_quotes(char **args);
char		*remove_quotes_from_str(char *str);
char		*ft_getenv(char *name, t_env *envp);
int			is_valid_var_char(char c, int first_char);
char		*replace_env_var(char *arg, int start, char *value, int var_len);
char		*get_cmd_path(char *cmd_name, char *path_var);
char		*set_full_cmd(char *current_path, char *cmd_name);
void		free_strs(char **strs);
char		**env_to_array(t_env *env);
int			is_builtin_cmd(char *cmd_name);
void		add_env_var(t_env *env, char *key, char *value);
int			count_args(char *str);
char		*extract_arg(char *str, int *i);
char		*remove_out_spaces(char *str);
char		*ft_getenv(char *name, t_env *envp);
int			is_valid_var_char(char c, int first_char);
void		update_status(t_env **envp, int status);
void		update_quote_state(char c, int *in_single_quote,
				int *in_double_quote);
int			is_quote(char c, int in_other_quote, char quote_type);
int			should_copy_char(char c, int in_single_quote, int in_double_quote);
int			process_quotes(char c, int *in_single_quote, int *in_double_quote);
void		toggle_quote(int *quote_flag);
int			are_quotes_close(char *str, char quote);
int			is_only_spaces(char *str);
int			handle_builtin_cmd(t_cmd_line cmd_line, t_shell *shell);
pid_t		exec_child_process(t_cmd cmd, t_shell *shell, int in_fd,
				int out_fd);
void		execute_builtin_or_external(t_cmd cmd, t_shell *shell,
				char *cmd_path);
int			handle_redirections_and_dup(int in_fd, int out_fd);
void		handle_redirections(t_cmd cmd);
int			handle_here_doc(char *delimiter);
void		handle_redirections(t_cmd cmd);
int			ft_printf(const char *str, ...);
/*----------------------- EXEC.C ---------------------------*/
int			exec_cmds(t_cmd_line cmd_line, t_shell *shell);
int			exec_cmd(t_cmd cmd, t_shell *shell, int in_fd, int out_fd);
int			exec_builtin(t_cmd cmd, t_shell *shell);
/*----------------------- EXEC.C ---------------------------*/

/*----------------------- ECHO.C ---------------------------*/
int			exec_echo(t_cmd cmd);
/*----------------------- ECHO.C ---------------------------*/

/*----------------------- CD.C ---------------------------*/
int			exec_cd(t_cmd cmd, t_env *env);
/*----------------------- CD.C ---------------------------*/

/*----------------------- PWD.C ---------------------------*/
int			exec_pwd(void);
/*----------------------- PWD.C ---------------------------*/

/*----------------------- UNSET.C ---------------------------*/
int			exec_unset(t_cmd cmd, t_env **envp);
/*----------------------- UNSET.C ---------------------------*/

/*----------------------- EXPORT.C ---------------------------*/
int			exec_export(t_cmd cmd, t_env **envp);
/*----------------------- EXPORT.C ---------------------------*/

/*----------------------- EXIT.C ---------------------------*/
int			exec_exit(t_cmd cmd);
/*----------------------- EXIT.C ---------------------------*/

#endif
