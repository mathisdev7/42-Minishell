/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:28:22 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/12 14:35:08 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (s != NULL || f != NULL)
	{
		while (s[i])
		{
			f(i, &s[i]);
			i++;
		}
	}
}

/*
void increment_char(unsigned int index, char *c) {
	(void)index;
    *c = *c + 1;
}

int main() {
    char *str = NULL;
    
    printf("before ft_striteri: %s\n", str);
    
    ft_striteri(str, increment_char);
    
    printf("after ft_striteri: %s\n", str);
}
*/
