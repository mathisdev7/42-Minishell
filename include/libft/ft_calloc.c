/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 07:55:23 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/09 00:02:11 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	while (count * size > i)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

/*
int main() {
    size_t n = 5;
    size_t *arr;

    arr = calloc(n, sizeof(int));

    if (arr == NULL) {
        printf("failed\n");
        return 1;
    }

    printf("after calloc:\n");
    for (size_t i = 0; i < n; i++) {
        printf("%zu ", arr[i]);
    }
    printf("\n");

    free(arr);

    return 0;
}
*/