/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:46:25 by vcaratti          #+#    #+#             */
/*   Updated: 2025/01/23 11:04:08 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	flip_flag(int *flag)
{
	if (*flag)
		*flag = 0;
	else
		*flag = 1;
}

int	check_quotes(char *str)
{
	int	count;
	int	flags[2];

	count = 0;
	flags[0] = 0;
	flags[1] = 0;
	while (str[count])
	{
		if ((int)str[count] == 39)
			flip_flag(&(flags[0]));
		if ((int)str[count] == 34)
			flip_flag(&(flags[1]));
		count++;
	}
	if (flags[0] || flags[1])
		return (1);
	return (0);
}
