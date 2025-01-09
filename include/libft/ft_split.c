/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:55:39 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/07 17:11:39 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(const char *str, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] && str[i] != c)
		{
			words++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (words);
}

int	s_len(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*fill_in_words(const char *str, int start, int end)
{
	int		len;
	char	*word;
	int		i;

	len = end - start;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_copy(const char *str, char c, char **result)
{
	int	start;
	int	end;
	int	current_pos;

	start = 0;
	end = 0;
	current_pos = 0;
	while (str[start])
	{
		while (str[start] == c)
			start++;
		end = start;
		while (str[end] && str[end] != c)
			end++;
		if (end > start)
		{
			result[current_pos] = fill_in_words(str, start, end);
			current_pos++;
		}
		start = end;
	}
	result[current_pos] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**str;
	int		i;

	words = count_words(s, c);
	i = 0;
	str = malloc(sizeof(char *) * (words + 1));
	if (!str)
	{
		return (NULL);
	}
	while (s[i] == c)
		i++;
	str = ft_copy(s, c, str);
	return (str);
}

// int	main(void)
// {
// 	char const	str[] = "   lorem   ipsum dolor     sit amet,
// consectetur   adipiscing elit. Sed non risus. Suspendisse   ";
// 	int			i;
// 	char		**splitted;

// 	i = 0;
// 	splitted = ft_split(str, ' ');
// 	while (splitted[i])
// 	{
// 		printf("%s\n", splitted[i]);
// 		i++;
// 	}
// }
