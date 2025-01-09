/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:55:53 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/06 22:44:41 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*res;

	i = 0;
	res = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (s[i])
	{
		res[i] = (*f)(i, s[i]);
		i++;
	}
	res[i] = 0;
	return (res);
}

/*
char add_offset(unsigned int index, char c) {
    return c + (char)index;
}

int main() {
    const char *src = "abcdef";

    printf("before ft_strmapi: %s\n", src);

    char *result = ft_strmapi(src, add_offset);

    if (result) {
        printf("after ft_strmapi: %s\n", result);
        free(result);
    } else {
        printf("Error\n");
    }
}
*/