/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:36:11 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/22 14:39:03 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	len3;

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

char	*create_prompt(char *cwd)
{
	char	*prompt;

	prompt = ft_strjoin3("\001\033[1;36m\002┌──(\001\033[1;33m\002",
			cwd,
			"\001\033[1;36m\002)\n└─\001\033[1;35m\002❯"
			"\001\033[1;36m\002❯\001\033[1;35m\002❯\001\033[0m\002 ");
	return (prompt);
}
