/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:43:00 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/12 15:04:20 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
		{
			result[j] = s[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

/*
int	main(void)
{
	char * s = ft_substr("tripouille", 0, 42000);
	printf("%s", s);
	return (0);
}
*/
