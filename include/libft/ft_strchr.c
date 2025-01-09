/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:03:38 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/06 23:09:21 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(&s[i]));
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(&s[i]));
	return (NULL);
}

/*
int main() {
    const char *str = "Hello, world!";
    char ch1 = 'o';
    char ch2 = 'z';
    char ch3 = '\0';

    char *result1 = ft_strchr(str, ch1);
    printf("finding '%c' in \"%s\": %s\n", 
	ch1, str, result1 ? result1 : "not found");

    char *result2 = ft_strchr(str, ch2);
    printf("finding '%c' in \"%s\": %s\n", 
	ch2, str, result2 ? result2 : "not found");

    char *result3 = ft_strchr(str, ch3);
    printf("finding '\\0' in \"%s\": %s\n", 
	str, result3 ? "found" : "not found");
}
*/
