/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:00:57 by vcaratti          #+#    #+#             */
/*   Updated: 2023/10/25 15:56:51 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skip_spaces(const char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	return (i);
}

static int	get_sign(const char *str, int *counter)
{
	int	sign;
	int	i;

	sign = 1;
	i = 0;
	while (str[*counter] == 45 || str[*counter] == 43)
	{
		if (str[*counter] == 45)
			sign = sign * -1;
		(*counter)++;
		i++;
	}
	if (i > 1)
		return (0);
	return (sign);
}

int	ft_atoi(const char *str)
{
	int	counter;
	int	end_int;
	int	sign;
	int	multiplier;
	int	result;

	counter = skip_spaces(str);
	sign = get_sign(str, &counter);
	if (sign == 0)
		return (0);
	end_int = counter;
	while (str[end_int] > 47 && str[end_int] < 58)
		end_int++;
	multiplier = 1;
	result = 0;
	while (end_int-- > counter)
	{
		result = result + ((str[end_int] - 48) * multiplier);
		multiplier = multiplier * 10;
	}
	return (result * sign);
}
