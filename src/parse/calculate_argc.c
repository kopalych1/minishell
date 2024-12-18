/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_argc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:39:51 by akostian          #+#    #+#             */
/*   Updated: 2024/12/18 15:48:56 by akostian         ###   ########.fr       */
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

int	treat_text(char **str, unsigned char *new_word, size_t *argc)
{
	while (**str && !ft_isspace(**str))
	{
		if (**str == '\'' || **str == '\"')
			*str = skip_quotes(*str);
		if (!(**str))
			return (-1);
		if (ft_strchr(">|<", **str))
		{
			if (*new_word)
				(*argc)++;
			if ((**str == '<' && *(*str + 1) == '<')
				|| (**str == '>' && *(*str + 1) == '>'))
				(*str)++;
			(*str)++;
			break ;
		}
		*new_word = 1;
		(*str)++;
	}
	return (0);
}

// Calculates amount of arguments passed by a user string
ssize_t	calculate_argc(char *str)
{
	size_t			argc;
	unsigned char	new_word;

	argc = 0;
	while (*str)
	{
		new_word = 0;
		while (*str && ft_isspace(*str))
			str++;
		if (treat_text(&str, &new_word, &argc) == -1)
			return (-1);
		if (*str || new_word || ft_strchr(">|<", *(str - 1)))
			argc++;
	}
	return (argc);
}
