/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:42:13 by vcaratti          #+#    #+#             */
/*   Updated: 2023/11/23 14:29:49 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	int				response;
	unsigned char	*s1temp;
	unsigned char	*s2temp;

	s1temp = (unsigned char *)s1;
	s2temp = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		response = s1temp[i] - s2temp[i];
		if (response != 0)
			return (response);
		else
			i++;
	}
	return (0);
}
