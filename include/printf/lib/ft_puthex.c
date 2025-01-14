/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 02:32:11 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/09 06:40:50 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_put_hex(unsigned int num, int uppercase)
{
	char	*hex;
	int		len;

	len = 0;
	if (uppercase)
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	if (num >= 16)
		len += ft_put_hex(num / 16, uppercase);
	ft_putchar_fd(hex[num % 16], 1);
	len += 1;
	return (len);
}
