/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:28:44 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/11 01:55:56 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    exec_builtin(t_cmd cmd, t_env **envp)
{
	int	status;

	status = 0;
	if (ft_strcmp(cmd.args[0], "cd") == 0)
		status = exec_cd(cmd, envp);
	else if (ft_strcmp(cmd.args[0], "echo") == 0)
		status = exec_echo(cmd, envp);
	else if (ft_strcmp(cmd.args[0], "pwd") == 0)
		status = exec_pwd();
	else if (ft_strcmp(cmd.args[0], "export") == 0)
		status = exec_export(cmd, envp);
	else if (ft_strcmp(cmd.args[0], "unset") == 0)
		status = exec_unset(cmd, envp);
	else if (ft_strcmp(cmd.args[0], "env") == 0)
		status = exec_env(cmd, envp);
	update_status(envp, status);
}
// ca c'est fait mtn tt les programmes dans path marchent (j'ai litteralement copie colle mon pipex)
void	exec_cmd(t_cmd cmd, t_env **envp)
{
	char	*path;
	char	**env_array;
	pid_t	pid;
	int		status;

	env_array = env_to_array(*envp);
	if (!env_array)
		return ;
	path = get_cmd_path(*envp, cmd.args[0]);
	if (!path)
	{
		printf("Command not found: %s\n", cmd.args[0]);
		update_status(envp, 127);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(path);
		free_split(env_array);
		return ;
	}
	if (pid == 0)
	{
		execve(path, cmd.args, env_array);
		perror("execve");
		free(path);
		free_split(env_array);
		exit(1);
	}
	else
	{
		waitpid(pid, &status, 0);
		free(path);
		free_split(env_array);
		if (WIFEXITED(status))
			update_status(envp, WEXITSTATUS(status));
	}
}