/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_length.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:03:04 by akostian          #+#    #+#             */
/*   Updated: 2024/10/23 16:58:12 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	get_var_length(char *str)
{
	size_t	length;

	str++;
	length = 1;
	while (*str && (ft_isalnum(*str) || *str == '_'))
	{
		str++;
		length++;
	}
	return (length - 1);
}
