/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:50:14 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/07 17:11:15 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

/*
int main() {
    char printable = 'A';
    char space = ' ';
    char non_printable = '\n';

    printf("A = %d\n", ft_isprint(printable));
    printf("Space = %d\n", ft_isprint(space));
    printf("\\n = %d\n", ft_isprint(non_printable));
}
*/
