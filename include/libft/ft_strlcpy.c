/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:51:19 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/06 22:41:45 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dstsize > src_len + 1)
	{
		ft_memcpy(dst, src, src_len + 1);
	}
	else if (dstsize != 0)
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = 0;
	}
	return (src_len);
}

/*
int main() {
    char dest[20];
    const char *src = "Hello, world!";

    printf("before ft_strlcpy: '%s'\n", dest);
    
    size_t result = ft_strlcpy(dest, src, sizeof(dest));
    
    printf("after ft_strlcpy: '%s'\n", dest);
    printf("size of the copied str: %zu\n", result);
    
    return 0;
}
*/