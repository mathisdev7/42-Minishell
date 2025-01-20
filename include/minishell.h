/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 03:47:03 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/14 03:47:03 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include <sys/types.h>
#include <sys/wait.h>
#include "structures.h"

/*----------------------- INIT.C ---------------------------*/
t_shell	*init_shell(char **envp);
t_env	*init_env(char **envp);
void	prompt_system(t_shell *shell);
/*----------------------- INIT.C ---------------------------*/


/*----------------------- FREE.C ---------------------------*/
void	free_shell(t_shell *shell);
/*----------------------- FREE.C ---------------------------*/


/*----------------------- DEBUG.C ---------------------------*/
void	print_cmd_args(t_cmd cmd);
void	print_redirections(t_cmd cmd);
/*----------------------- DEBUG.C ---------------------------*/


/*----------------------- PARSING.C ---------------------------*/
t_cmd_line	parse_cmd_line(char *line, t_env *envp);
t_cmd	parse_cmd(char *cmd_line, t_env *envp, int pipe_presence);
void	parse_env_vars(char	**args, t_env *envp);
char *remove_redirections(char *cmd_line);
char *get_redir_file(char *cmd_line, int start);
/*----------------------- PARSING.C ---------------------------*/


/*----------------------- UTILS.C ---------------------------*/
char	**ft_split_args(char *str);
char	*remove_out_spaces(char *str);
char	**remove_out_quotes(char **args);
char	*remove_quotes_from_str(char *str);
char	*ft_getenv(char *name, t_env *envp);
int		is_valid_var_char(char c, int first_char);
char	*replace_env_var(char *arg, int start, char *value, int var_len);
char	*get_cmd_path(char *cmd_name, char *path_var);
char	*set_full_cmd(char *current_path, char *cmd_name);
void	free_strs(char **strs);
char	**env_to_array(t_env *env);
int	is_builtin_cmd(char *cmd_name);
char	*ft_getenv(char *name, t_env *envp);
t_env	*update_env(t_env **envp, char *name, char *value);
void	update_status(t_env **envp, int status);
char	**env_to_array(t_env *env);
/*----------------------- UTILS.C ---------------------------*/


/*----------------------- EXEC.C ---------------------------*/
int	exec_cmds(t_cmd_line cmd_line, t_shell *shell);
void	execute_pipeline(t_cmd_line cmd_line, t_shell *shell,
	int *prev_pipe, pid_t *last_pid);
void	wait_for_processes(pid_t last_pid, int *status);
/*----------------------- EXEC.C ---------------------------*/


/*----------------------- ECHO.C ---------------------------*/
int	exec_echo(t_cmd cmd);
/*----------------------- ECHO.C ---------------------------*/


/*----------------------- CD.C ---------------------------*/
int	exec_cd(t_cmd cmd, t_env *env);
/*----------------------- CD.C ---------------------------*/


/*----------------------- PWD.C ---------------------------*/
int	exec_pwd();
/*----------------------- PWD.C ---------------------------*/


/*----------------------- UNSET.C ---------------------------*/
int	exec_unset(t_cmd cmd, t_env **envp);
/*----------------------- UNSET.C ---------------------------*/


/*----------------------- EXPORT.C ---------------------------*/
int	exec_export(t_cmd cmd, t_env **envp);
/*----------------------- EXPORT.C ---------------------------*/


/*----------------------- EXIT.C ---------------------------*/
int	exec_exit(t_cmd cmd, t_shell *shell);
/*----------------------- EXIT.C ---------------------------*/

/*----------------------- FREE.C ---------------------------*/
void	free_env(t_env *env);
void	free_shell(t_shell *shell);
void	free_cmd_line(t_cmd_line *cmd_line);
/*----------------------- FREE.C ---------------------------*/


/*----------------------- REDIRECTIONS.C ---------------------------*/
void	parse_redirections(t_cmd *cmd, char *cmd_line);
int	set_in_redir(t_cmd *cmd, int *i, int *redir_index, char *cmd_line);
int	set_out_redir(t_cmd *cmd, int *i, int *redir_index, char *cmd_line);
/*----------------------- REDIRECTIONS.C ---------------------------*/


/*----------------------- REDIRECTIONS.C ---------------------------*/
int 	open_redir_file(t_redirection redir);
int		handle_here_doc(char *delimiter);
int		handle_redirections(t_cmd cmd);
/*----------------------- REDIRECTIONS.C ---------------------------*/


/*----------------------- CMD.C ---------------------------*/
void	setup_io_redirections(int in_fd, int out_fd);
void	handle_cmd_not_found(char *cmd_arg);
int exec_cmd(t_cmd cmd, t_shell *shell, int in_fd, int out_fd);
int		exec_builtin(t_cmd cmd, t_shell *shell);
/*----------------------- CMD.C ---------------------------*/

#endif
