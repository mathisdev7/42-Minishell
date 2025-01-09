/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:25:00 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/05 00:18:46 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	total_len;
	size_t	i;
	size_t	j;
	char	*result;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	j = 0;
	result = malloc(sizeof(char *) * total_len + 1);
	if (!result)
		return (NULL);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}
/*
int	main(void)
{
	char	*s1;
	char	*s2;

	s1 = "hello ";
	s2 = "world";
	printf("%s", ft_strjoin(s1, s2));
}
*/
