/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:22:32 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/09 15:22:32 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft/libft.h"
#include "../include/minishell.h"

void    free_split(char **splitted)
{
    int i;

    i = 0;
    while (splitted[i])
    {
        free(splitted[i]);
        i++;
    }
    free(splitted);
}

char	**ft_split_args(char *cmd_line)
{
    char	**args;
    int		i;
    int		j;
    int		start;
    char	quote;
    int		in_quote;
    int		arg_count;

    if (!cmd_line)
        return (NULL);
    arg_count = count_args(cmd_line) + 1;
    args = malloc(sizeof(char *) * (arg_count + 1));
    if (!args)
        return (NULL);
    i = 0;
    j = 0;
    while (cmd_line[i] && j < arg_count)
    {
        while (cmd_line[i] && cmd_line[i] == ' ')
            i++;  
        start = i;
        in_quote = 0;
        while (cmd_line[i] && (in_quote || cmd_line[i] != ' '))
        {
            if (cmd_line[i] == '"' || cmd_line[i] == '\'')
            {
                if (!in_quote)
                {
                    quote = cmd_line[i];
                    in_quote = 1;
                }
                else if (cmd_line[i] == quote)
                    in_quote = 0;
            }
            i++;
        }
        args[j] = malloc(sizeof(char) * (i - start + 1));
        if (!args[j])
        {
            free_split(args);
            return (NULL);
        }
        ft_strncpy(args[j], &cmd_line[start], i - start);
        j++;
    }
    args[j] = NULL;
    return (args);
}

void ft_env_remove_if(t_env **begin_list, char *data_ref, int (*cmp)(char *, char *))
{
    if (begin_list == NULL || *begin_list == NULL)
        return;

    t_env *cur = *begin_list;
    if (cmp(cur->name, data_ref) == 0)
    {
        *begin_list = cur->next;
        free(cur->name);
        free(cur->value);
        free(cur);
        ft_env_remove_if(begin_list, data_ref, cmp);
    }
    else
    {
        ft_env_remove_if(&cur->next, data_ref, cmp);
    }
}

char	*set_full_cmd(char *current_path, char *cmd_name)
{
	char	*full_cmd;
	char	*cmd_path;
	char	slash[2];

	slash[0] = '/';
	slash[1] = '\0';
	cmd_path = ft_strjoin(current_path, slash);
	full_cmd = ft_strjoin(cmd_path, cmd_name);
	free(cmd_path);
	return (full_cmd);
}

char	**get_splitted_path(t_env *envp)
{
    char	*path_value;
    char	**splitted_path;

    path_value = ft_getenv("PATH", envp);
    if (!path_value)
        return (NULL);
    splitted_path = ft_split(path_value, ':');
    if (!splitted_path)
        return (NULL);
    return (splitted_path);
}

char	*get_cmd_path(t_env *envp, char *cmd_name)
{
    int		i;
    char	**splitted_path;
    char	*full_cmd;

    i = 0;
    if (cmd_name[0] == '/' || cmd_name[0] == '.')
    {
        if (access(cmd_name, X_OK) == 0)
            return (ft_strdup(cmd_name));
        return (NULL);
    }
    splitted_path = get_splitted_path(envp);
    if (!splitted_path)
        return (NULL);
    while (splitted_path[i])
    {
        full_cmd = set_full_cmd(splitted_path[i], cmd_name);
        if (access(full_cmd, X_OK) == 0)
        {
            free_split(splitted_path);
            return (full_cmd);
        }
        free(full_cmd);
        i++;
    }
    free_split(splitted_path);
    return (NULL);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char *ft_getenv(char *name, t_env *envp)
{
    t_env *current;

    if (!name || !envp)
        return (NULL);

    current = envp;
    while (current)
    {
        if (ft_strcmp(current->name, name) == 0)
            return current->value;
        current = current->next;
    }
    return (NULL);
}

int count_args(char *str)
{
    int count;

	count = 0;
    char *ptr = str;

    while (*ptr)
	{
        while (*ptr && *ptr == ' ')
            ptr++;
        if (*ptr)
		{
            count++;
            while (*ptr && *ptr != ' ')
                ptr++;
        }
    }
    return (count - 1);
}

t_env *init_env(char **envp)
{
    t_env *env = NULL;
    t_env *new_node;
    int i = 0;

    while (envp[i])
    {
        new_node = malloc(sizeof(t_env));
        if (!new_node)
            return NULL;
        new_node->name = strdup(strtok(envp[i], "="));
        new_node->value = strdup(strtok(NULL, "="));
        new_node->next = env;
        env = new_node;
        i++;
    }
    return env;
}

void free_env(t_env *env)
{
    t_env *temp;
    while (env)
    {
        temp = env;
        env = env->next;
        free(temp->name);
        free(temp->value);
        free(temp);
    }
}

char *ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char    **env_to_array(t_env *envp)
{
    int     count;
    char    **array;
    t_env   *current;
    int     i;
    char    *tmp;

    count = 0;
    current = envp;
    while (current)
    {
        count++;
        current = current->next;
    }
    array = malloc(sizeof(char *) * (count + 1));
    if (!array)
        return (NULL);
    i = 0;
    current = envp;
    while (current)
    {
        tmp = ft_strjoin3(current->name, "=", current->value);
        if (!tmp)
        {
            free_split(array);
            return (NULL);
        }
        array[i++] = tmp;
        current = current->next;
    }
    array[i] = NULL;
    return (array);
} 

char    *ft_strjoin3(char *s1, char *s2, char *s3)
{
    char    *result;
    size_t  len1;
    size_t  len2;
    size_t  len3;

    if (!s1 || !s2 || !s3)
        return (NULL);
    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    len3 = ft_strlen(s3);
    result = malloc(sizeof(char) * (len1 + len2 + len3 + 1));
    if (!result)
        return (NULL);
    ft_strcpy(result, s1);
    ft_strcpy(result + len1, s2);
    ft_strcpy(result + len1 + len2, s3);

    return (result);
}


