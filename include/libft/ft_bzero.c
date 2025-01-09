/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:48:32 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/06 21:57:09 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*s2;

	s2 = (char *)s;
	while (n > 0)
	{
		(*s2++) = 0;
		n--;
	}
}
/*
int main()
{
    char buffer[10];

    for (int i = 0; i < 10; i++) {
        buffer[i] = 'A';
    }

    printf("before bzero: ");
    for (int i = 0; i < 10; i++) {
        printf("%c ", buffer[i]);
    }
    printf("\n");

    bzero(buffer, 10);

    printf("after bzero: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    return 0;
}
*/
