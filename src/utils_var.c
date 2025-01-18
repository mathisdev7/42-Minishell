/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:01:03 by mazeghou          #+#    #+#             */
/*   Updated: 2025/01/18 11:02:46 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_valid_var_char(char c, int first_char)
{
	if (first_char)
		return (ft_isalpha(c) || c == '_' || c == '?');
	return (ft_isalnum(c) || c == '_');
}
