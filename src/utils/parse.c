char	*expand_variables(char *arg, t_env *envp)
{
	char	*expanded;
	char	*value;

	if (arg[0] != '$')
		return (ft_strdup(arg));

	if (arg[1] == '?')
		value = ft_getenv("?", envp);
	else
		value = ft_getenv(arg + 1, envp);

	if (!value)
		return (ft_strdup(""));

	expanded = ft_strdup(value);
	return (expanded);
}

t_cmd	parse_cmd(char *cmd_line, t_env **envp)
{
	t_cmd	cmd;
	char	**args;
	int		i;
	char	*expanded;

	args = ft_split_args(cmd_line);
	cmd.args = malloc(sizeof(char *) * (count_args(cmd_line) + 1));
	i = 0;
	while (args[i])
	{
		if (args[i][0] == '$')
		{
			expanded = expand_variables(args[i], *envp);
			cmd.args[i] = expanded;
		}
		else
			cmd.args[i] = ft_strdup(args[i]);
		i++;
	}
	cmd.args[i] = NULL;
	free_split(args);
	return (cmd);
}
