/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:34:36 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/06 22:25:37 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;

	if (dst == (void *)0 && src == (void *)0)
	{
		return (dst);
	}
	tmp_dst = (unsigned char *)dst;
	tmp_src = (unsigned char *)src;
	while (n > 0)
	{
		*(tmp_dst++) = *(tmp_src++);
		n--;
	}
	return (dst);
}

/*
int main()
{
	char buffer[10];
	char buffer2[5] = "salut";

	for (size_t i = 0; i < 10; i++)
	{
		buffer[i] = 'a' + i;
	}
	printf("before memcpy: %s\n", buffer);
	ft_memcpy(buffer, buffer2, 10);
	printf("after memcpy: %s\n", buffer);
}
*/