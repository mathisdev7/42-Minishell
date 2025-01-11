/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:29:29 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/11 01:32:15 by nopareti         ###   ########.fr       */
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

typedef struct s_cmd
{
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

void	exec_builtin(t_cmd cmd, t_env **envp);
void	exec_cmd(t_cmd cmd, t_env **envp);
int	exec_echo(t_cmd cmd, t_env **envp);
int		exec_cd(t_cmd cmd, t_env **envp);
int	exec_pwd(void);
int	exec_unset(t_cmd cmd, t_env **envp);
int		exec_export(t_cmd cmd, t_env **envp);
int		exec_env(t_cmd cmd, t_env **envp);

char	*ft_strncpy(char *dest, char *src, unsigned int n);
size_t	ft_strcspn(const char *s, const char *reject);
t_env	*init_env(char **envp);
void	free_env(t_env *env);
char	*ft_getenv(char *name, t_env *envp);
int		is_builtin_cmd(char **cmd_args);
void	ft_env_remove_if(t_env **begin_list, char *data_ref, int (*cmp)(char *, char *));
char	*get_cmd_path(t_env *envp, char *cmd_name);
char	**get_splitted_path(t_env *envp);
char	*set_full_cmd(char *current_path, char *cmd_name);

char	**ft_split_args(char *cmd_line);

void	update_status(t_env **envp, int status);

char    **env_to_array(t_env *envp);

char    *ft_strjoin3(char *s1, char *s2, char *s3);
char	*ft_strcpy(char *dest, char *src);

#endif
