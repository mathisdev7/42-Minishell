/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:03:38 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/06 22:59:24 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*occ;

	i = 0;
	occ = NULL;
	if (s == NULL)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			occ = (char *)&s[i];
		i++;
	}
	if (s[i] == (char)c)
		occ = (char *)&s[i];
	return (occ);
}

/*
int main()
{
    const char *str = "Hello, this is a test string.";

    printf("test 1: %s\n", ft_strrchr(str, 's'));

    printf("test 2: %s\n", ft_strrchr(str, 'o'));

    printf("test 3: %s\n", ft_strrchr(str, 'z')); 

    printf("test 4: %s\n", ft_strrchr(str, ','));

    printf("test 5: %s\n", ft_strrchr(str, ' '));

    printf("test 6: %s\n", ft_strrchr(str, '\0'));
}
*/