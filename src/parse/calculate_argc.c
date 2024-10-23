/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_argc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:39:51 by akostian          #+#    #+#             */
/*   Updated: 2024/10/23 16:58:17 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*skip_quotes(char *str)
{
	char	quote_to_find;

	quote_to_find = *str;
	str++;
	while (*str && *str != quote_to_find)
		str++;
	return (str);
}

// Calculates amount of arguments passed by a user string
ssize_t	calculate_argc(char *str)
{
	size_t			argc;
	unsigned char	new_word;

	argc = 0;
	while (*str)
	{
		while (*str && ft_isspace(*str))
		{
			new_word = 0;
			str++;
		}
		while (*str && !ft_isspace(*str))
		{
			if (*str == '\'' || *str == '\"')
				str = skip_quotes(str);
			if (!*str)
				return (-1);
			str++;
			new_word = 1;
		}
		if (*str || new_word)
			argc++;
	}
	return (argc);
}
