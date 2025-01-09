/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 07:41:04 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/06 22:40:12 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	copy_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dst_len >= dstsize)
		return (dstsize + src_len);
	copy_len = dstsize - dst_len - 1;
	if (copy_len > src_len)
		ft_memcpy(dst + dst_len, src, src_len + 1);
	else
	{
		ft_memcpy(dst + dst_len, src, copy_len);
	}
	dst[dst_len + copy_len] = '\0';
	return (dst_len + src_len);
}

/*
int main() {
    char dest[20] = "Hello, ";
    const char *src = "world!";
    
    printf("before ft_strlcat: '%s'\n", dest);
    
    size_t result = ft_strlcat(dest, src, sizeof(dest));
    
    printf("after ft_strlcat: '%s'\n", dest);
    printf("total size of the concatenated str : %zu\n", result);
}
*/
