/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:02:39 by vcaratti          #+#    #+#             */
/*   Updated: 2023/11/03 13:45:39 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calculnbr(int n)
{
	int	i;

	i = 1;
	if (n == -2147483648)
		n = -2147483647;
	if (n < 0)
		n = -n;
	while (n / 10 > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static int	treat_negative(int *n, char *str, int index, int *len)
{
	if (*n < 0)
	{
		str[index++] = '-';
		if (*n == -2147483648)
		{
			str[index++] = '2';
			*n += 2000000000;
			*len -= 1;
		}
		*n = -(*n);
	}
	return (index);
}

char	*ft_itoa(int n)
{
	int		index;
	int		len;
	char	*str;

	index = 0;
	len = calculnbr(n);
	str = (char *)malloc(len + 1 + (1 * (n < 0)) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[len + (1 * (n < 0))] = '\0';
	index = treat_negative(&n, str, index, &len);
	while (len > 0)
	{
		str[len + index - 1] = n % 10 + '0';
		n /= 10;
		len--;
	}
	return (str);
}
