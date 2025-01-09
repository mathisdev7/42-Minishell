/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:51:21 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/11 11:41:25 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, const char *set)
{
	int		start;
	int		end;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (start <= end && ft_strchr(set, s1[start]))
		start++;
	if (start > end)
	{
		return (ft_strdup(s1 + end + 1));
	}
	while (end >= 0 && ft_strchr(set, s1[end]))
		end--;
	result = malloc(sizeof * result * (end - start) + 2);
	if (!result)
		return (NULL);
	ft_strlcpy(result, &s1[start], end - start + 2);
	return (result);
}

// int	main(void)
// {
// 	char	*set;

// 	char *str = "lorem ipsum dolor sit amet"; 
// 	set = "te";
// 	printf("%s", ft_strtrim(str, set));
// }
