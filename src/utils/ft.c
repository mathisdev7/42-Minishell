/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:59:37 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/10 14:59:37 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i;
	size_t	i2;

	i = 0;
	i2 = 0;
	while (s[i] != '\0')
	{
		i2 = 0;
		while (reject[i2] != '\0')
		{
			if (s[i] == reject[i2])
				return (i);
			i2++;
		}
		i++;
	}
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
