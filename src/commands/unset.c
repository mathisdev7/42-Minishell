#include "../include/minishell.h"

void	exec_unset(t_cmd cmd, t_env **envp)
{
	cmd.args++;
	while (*cmd.args)
	{
    	ft_env_remove_if(envp, *cmd.args, ft_strcmp);
		cmd.args++;
	}
}
