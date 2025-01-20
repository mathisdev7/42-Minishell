/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 00:56:48 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/20 14:04:12 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	printf_putstr_fd(char *s, int fd);
int	printf_putnbr_fd(int n, int fd);
int	ft_put_ptr(void *ptr, int first);
int	printf_strlen(const char *str);
int	printf_putchar_fd(char c, int fd);
int	ft_put_hex(unsigned int num, int uppercase);
int	ft_put_unsigned(unsigned int n);

#endif
