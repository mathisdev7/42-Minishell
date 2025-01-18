/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 00:56:26 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/09 06:41:37 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_format(va_list args, char format, int print_len, void *p)
{
	char	*str;

	if (format == 's')
	{
		str = va_arg(args, char *);
		if (!str)
			return (ft_putstr_fd("(null)", 1));
		print_len = ft_putstr_fd(str, 1);
	}
	else if (format == 'c')
		print_len = ft_putchar_fd(va_arg(args, int), 1);
	else if (format == 'p')
	{
		p = va_arg(args, void *);
		print_len = ft_put_ptr(p, 0);
	}
	else if (format == 'd' || format == 'i')
		print_len = ft_putnbr_fd(va_arg(args, int), 1);
	else if (format == 'u')
		print_len = ft_put_unsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		print_len = ft_put_hex(va_arg(args, unsigned int), format == 'X');
	else if (format == '%')
		print_len = ft_putchar_fd('%', 1);
	return (print_len);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	i;
	int		print_len;
	void	*p;

	i = 0;
	print_len = 0;
	p = NULL;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			print_len += ft_print_format(args, str[i], print_len, p);
		}
		else
		{
			write(1, &str[i], 1);
			print_len += 1;
		}
		i++;
	}
	va_end(args);
	return (print_len);
}

/*
int	main(void)
{
	int	ret_original;
	int	ret_custom;
	int	x;

	ret_original = printf("Original: %s\n", "Hello, World!");
	ret_custom = ft_printf("Custom  : %s\n", "Hello, World!");
	printf("Length original: %d, Length custom: %d\n\n", ret_original,
		ret_custom);
	ret_original = printf("Original: %s\n", (char *)NULL);
	ret_custom = ft_printf("Custom  : %s\n", (char *)NULL);
	printf("Length original: %d, Length custom: %d\n\n", ret_original,
		ret_custom);
	ret_original = printf("Original: %c %c %c\n", 'A', 'B', 'C');
	ret_custom = ft_printf("Custom  : %c %c %c\n", 'A', 'B', 'C');
	printf("Length original: %d, Length custom: %d\n\n", ret_original,
		ret_custom);
	x = 42;
	ret_original = printf("Original: %p\n", (void *)&x);
	ret_custom = ft_printf("Custom  : %p\n", (void *)&x);
	printf("Length original: %d, Length custom: %d\n\n", ret_original,
		ret_custom);
	ret_original = printf("Original: %d %i\n", -1234, 5678);
	ret_custom = ft_printf("Custom  : %d %i\n", -1234, 5678);
	printf("Length original: %d, Length custom: %d\n\n", ret_original,
		ret_custom);
	ret_original = printf("Original: %u\n", 4294967295u);
	ret_custom = ft_printf("Custom  : %u\n", 4294967295u);
	printf("Length original: %d, Length custom: %d\n\n", ret_original,
		ret_custom);
	ret_original = printf("Original: %x %X\n", 3735928559u, 3735928559u);
	ret_custom = ft_printf("Custom  : %x %X\n", 3735928559u, 3735928559u);
	printf("Length original: %d, Length custom: %d\n\n", ret_original,
		ret_custom);
	ret_original = printf("Original: %%\n");
	ret_custom = ft_printf("Custom  : %%\n");
	printf("Length original: %d, Length custom: %d\n\n", ret_original,
		ret_custom);
	ret_original = printf("Original: %s %c %d %u %x %p %%\n", "Test", 'A', -123,
			123456789u, 255, &x);
	ret_custom = ft_printf("Custom  : %s %c %d %u %x %p %%\n", "Test", 'A',
			-123, 123456789u, 255, &x);
	printf("Length original: %d, Length custom: %d\n\n", ret_original,
		ret_custom);
	return (0);
}
*/
