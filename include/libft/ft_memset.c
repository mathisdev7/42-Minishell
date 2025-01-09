/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:32:46 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/06 22:34:56 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (len > 0)
	{
		*(ptr++) = (unsigned char)c;
		len--;
	}
	return (b);
}

/*
int main() {
    char buffer[10];

    for (size_t i = 0; i < 10; i++) {
        buffer[i] = 'a' + i;
    }
    buffer[9] = '\0';

    printf("before memset: %s\n", buffer);

    ft_memset(buffer, 'X', 5);

    printf("after memset: %s\n", buffer);
}
*/
