/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:50:14 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/07 17:10:56 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

/*
int main()
{
	char al = 'a';
	char al2 = 'z';
	char not_al = '+';
	printf("a = %d\n", ft_isalpha(al));
	printf("z = %d\n", ft_isalpha(al2));
	printf("not a = %d\n", ft_isalpha(not_al));
}
*/
