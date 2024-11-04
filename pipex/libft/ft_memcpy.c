/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:59:37 by vcaratti          #+#    #+#             */
/*   Updated: 2023/10/26 13:52:10 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned long	i;
	unsigned char	*dsttemp;
	unsigned char	*srctemp;

	dsttemp = (unsigned char *)dst;
	srctemp = (unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dsttemp[i] = srctemp[i];
		i++;
	}
	return (dst);
}
