/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:50:14 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/06 22:10:35 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (c);
	else
		return (0);
}

/*
int main() {
    char num1 = '3';
    char num2 = '9';
    char not_num = 'a';

    printf("3 = %d\n", ft_isdigit(num1));
    printf("9 = %d\n", ft_isdigit(num2));
    printf("a = %d\n", ft_isdigit(not_num));
}
*/