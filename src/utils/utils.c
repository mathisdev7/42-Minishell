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


