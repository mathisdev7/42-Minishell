/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:12:47 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/06 23:11:36 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		if (s1[i] == '\0' && s2[i] == '\0')
			break ;
		i++;
	}
	return (0);
}

/*
int main() {
    printf("Test 1 (equal strings): %d\n", 
	ft_strncmp("hello", "hello", 5));
    printf("Test 2 (different at position 5): %d\n", 
	ft_strncmp("hello", "hella", 5));
    printf("Test 3 (lengths differ): %d\n", 
	ft_strncmp("hello", "hello, world!", 5));
    printf("Test 4 (stop at n): %d\n", 
	ft_strncmp("hello", "helloworld", 7));   
}
*/