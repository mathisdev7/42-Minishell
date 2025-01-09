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

int count_cmd(char *str)
{
    int count = 0;
    char *ptr = str;

    while (*ptr) {
        while (*ptr && *ptr == ' ')
            ptr++;
        if (*ptr)
		{
            count++;
            while (*ptr && *ptr != ' ')
                ptr++;
        }
    }

    return count;
}
