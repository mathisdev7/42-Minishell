/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:28:44 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/11 23:47:01 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_builtin(t_cmd cmd, t_env **envp)
{
	int	status;

	status = 0;
	if (ft_strcmp(cmd.args[0], "cd") == 0)
		status = exec_cd(cmd, envp);
	else if (ft_strcmp(cmd.args[0], "echo") == 0)
		status = exec_echo(cmd, envp);
	else if (ft_strcmp(cmd.args[0], "pwd") == 0)
		status = exec_pwd(cmd);
	else if (ft_strcmp(cmd.args[0], "export") == 0)
		status = exec_export(cmd, envp);
	else if (ft_strcmp(cmd.args[0], "unset") == 0)
		status = exec_unset(cmd, envp);
	else if (ft_strcmp(cmd.args[0], "env") == 0)
		status = exec_env(cmd, envp);
	else if (ft_strcmp(cmd.args[0], "exit") == 0)
		status = exec_exit(cmd, envp);
	update_status(envp, status);
}

static void	execute_child_process(char *path, t_cmd cmd, char **env_array)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(path, cmd.args, env_array);
	perror("execve");
	free(path);
	free_split(env_array);
	exit(1);
}

static void	handle_command_not_found(t_cmd cmd, t_env **envp, char **env_array)
{
	printf("Command not found: %s\n", cmd.args[0]);
	update_status(envp, 127);
	free_split(env_array);
}

static void	handle_process(char *path, t_cmd cmd,
char **env_array, t_env **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(path);
		free_split(env_array);
		return ;
	}
	if (pid == 0)
		execute_child_process(path, cmd, env_array);
	waitpid(pid, &status, 0);
	free(path);
	free_split(env_array);
	if (status != -1)
		update_status(envp, status >> 8);
}

void	exec_cmd(t_cmd cmd, t_env **envp)
{
	char	*path;
	char	**env_array;

	env_array = env_to_array(*envp);
	if (!env_array)
		return ;
	path = get_cmd_path(*envp, cmd.args[0]);
	if (!path)
	{
		handle_command_not_found(cmd, envp, env_array);
		return ;
	}
	handle_process(path, cmd, env_array, envp);
}
