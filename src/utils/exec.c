/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:28:44 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/14 10:25:35 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_builtin(t_cmd cmd, t_env **envp)
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
	return (status);
}

static void	handle_command_not_found(t_cmd cmd, t_env **envp, char **env_array)
{
	ft_printf("Command not found: %s\n", cmd.args[0]);
	update_status(envp, 127);
	free_split(env_array);
}

static int	handle_process(char *path, t_cmd cmd,
char **env_array)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(path);
		free_split(env_array);
		return (127);
	}
	if (pid == 0)
	{
		execve(path, cmd.args, env_array);
		ft_printf("fork failed\n");
		perror("execve");
		free(path);
		free_split(env_array);
		exit(127);
	}
	waitpid(pid, &status, 0);
	free(path);
	free_split(env_array);
	return (status);
}

int	exec_cmd(t_cmd cmd, t_env **envp)
{
	char	*path;
	char	**env_array;
	int		status;

	status = 0;
	env_array = env_to_array(*envp);
	if (!env_array)
		return (status);
	path = get_cmd_path(*envp, cmd.args[0]);
	if (!path)
	{
		handle_command_not_found(cmd, envp, env_array);
		return (status);
	}
	status = handle_process(path, cmd, env_array);
	return (status);
}

int	child_process(t_cmd cmd, t_env **envp, int p_fd[2])
{
	int	status;

	status = 0;
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[0]);
	if (is_builtin_cmd(cmd.args))
		exec_builtin(cmd, envp);
	else
		status = exec_cmd(cmd, envp);
	return (status);
}

int	parent_process(t_cmd cmd, t_env **envp, int p_fd[2])
{
	int	status;

	status = 0;
	dup2(p_fd[0], STDIN_FILENO);
	close(p_fd[1]);
	if (is_builtin_cmd(cmd.args))
		exec_builtin(cmd, envp);
	else
		status = exec_cmd(cmd, envp);
	return (status);
}

int	exec_pipe_cmd(t_cmd_line cmd_line, t_env **envp)
{
	int		p_fd[2];
	pid_t	pid;
	int		status;

	if (pipe(p_fd) == -1)
	{
		perror("minishell: pipe");
		return (127);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (127);
	}
	if (!pid)
		status = child_process(cmd_line.cmds[0], envp, p_fd);
	else
		status = parent_process(cmd_line.cmds[1], envp, p_fd);
	close(p_fd[0]);
	close(p_fd[1]);
	return (status);
}
