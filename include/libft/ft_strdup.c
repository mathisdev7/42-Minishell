/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 08:06:52 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/06 22:34:48 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	size_t	i;

	dst = malloc(ft_strlen(s1) + 1);
	i = 0;
	if (!dst)
		return (NULL);
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

/*
int main() {
    const char *original = "Hello, world!";
    
    char *duplicate = ft_strdup(original);
    
    if (duplicate == NULL) {
        printf("error\n");
        return 1;
    }

    printf("original: %s\n", original);
    printf("duplicate: %s\n", duplicate);

    free(duplicate);
}
*/