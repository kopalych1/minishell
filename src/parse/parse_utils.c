/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:53:02 by akostian          #+#    #+#             */
/*   Updated: 2024/12/18 16:17:17 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

unsigned long	ft_ulmax(unsigned long a, unsigned long b)
{
	if (a > b)
		return (a);
	return (b);
}

size_t	treat_symbols(char **str, size_t *length)
{
	char	quote_to_find;

	if (**str == '\'' || **str == '\"')
	{
		quote_to_find = *(*str)++;
		(*length)++;
		while (**str && **str != quote_to_find)
		{
			(*str)++;
			(*length)++;
		}
	}
	if (ft_strchr(">|<", **str))
	{
		if (**str == '<' && *(*str + 1) == '<')
			return (ft_ulmax(*length, 2));
		if (**str == '>' && *(*str + 1) == '>')
			return (ft_ulmax(*length, 2));
		return (ft_ulmax(*length, 1));
	}
	return (0);
}

size_t	get_next_arg_len(char *str)
{
	size_t	length;
	size_t	ret;

	length = 0;
	while (*str && !ft_isspace(*str))
	{
		ret = treat_symbols(&str, &length);
		if (ret)
			return (ret);
		length++;
		str++;
	}
	return (length);
}
