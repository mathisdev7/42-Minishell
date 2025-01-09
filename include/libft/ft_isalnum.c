/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:50:14 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/06 22:00:25 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
		return (1);
	else
		return (0);
}

/*
int main()
{
	char al = 'a';
	char not_al = '+';
	char num = '2';
	char not_num = '-';
	printf("a = %d\n", ft_isalnum(al));
	printf("not a = %d\n", ft_isalnum(not_al));
	printf("num = %d\n", ft_isalnum(num));
	printf("not_num = %d\n", ft_isalnum(not_num));
}
*/