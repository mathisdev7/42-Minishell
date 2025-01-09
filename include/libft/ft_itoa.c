/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:28:34 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/06 05:13:16 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	num_len(int n, int index)
{
	long	nbr;

	nbr = n;
	if (nbr < 0)
	{
		index++;
		nbr = -nbr;
	}
	if (nbr < 10)
		return (index + 1);
	else
		return (num_len(nbr / 10, index + 1));
}

char	*ft_itoa(int n)
{
	char	*result;
	int		nb;
	int		i;
	long	nbr;

	nbr = n;
	nb = num_len(n, 0);
	result = malloc(sizeof(char) * (nb + 1));
	if (!result)
		return (NULL);
	i = nb - 1;
	if (nbr < 0)
		nbr = -nbr;
	while (nbr != 0)
	{
		result[i] = ((nbr % 10) + '0');
		nbr /= 10;
		i--;
	}
	if (n < 0)
		result[0] = '-';
	else if (n == 0)
		result[0] = '0';
	result[nb] = '\0';
	return (result);
}

/*
int main (void)
{
	int	nb;

	nb = -10;
	printf("%s\n", ft_itoa(nb));
}
*/
