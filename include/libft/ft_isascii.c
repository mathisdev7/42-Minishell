/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:50:14 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/07 17:11:10 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}

/*
int main() {
    char c1 = 'a';
    char c2 = '\n';

    printf("a = %d\n", ft_isascii(c1));
    printf("\\n = %d\n", ft_isascii(c2));
}
*/
