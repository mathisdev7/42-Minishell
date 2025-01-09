/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 07:47:33 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/06 22:56:32 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[0] == 0)
	{
		return ((char *)big);
	}
	while (big[i] && len > i)
	{
		while (big[i + j] && big[i + j] == little[j] && len > i + j)
		{
			j++;
			if (little[j] == 0)
				return ((char *)big + i);
		}
		i++;
		j = 0;
	}
	return (0);
}

/*
int main()
{
    const char *big = "Hello, this is a test string.";
    const char *little1 = "test";
    const char *little2 = "world";
    const char *little3 = "this";

    printf("test 1: %s\n", ft_strnstr(big, little1, 10));

    printf("test 2: %s\n", ft_strnstr(big, little1, 100));

    printf("test 3: %s\n", ft_strnstr(big, little2, 100));

    printf("test 4: %s\n", ft_strnstr(big, little3, 15));
}
*/