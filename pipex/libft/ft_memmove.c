/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:10:54 by vcaratti          #+#    #+#             */
/*   Updated: 2023/10/25 14:32:15 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dsttemp;
	unsigned char	*srctemp;
	unsigned int	i;

	dsttemp = (unsigned char *)dst;
	srctemp = (unsigned char *)src;
	i = 0;
	if (!dst && !src)
		return (0);
	if (dst > src)
	{
		while (len > 0)
		{
			dsttemp[len - 1] = srctemp[len - 1];
			len--;
		}
	}
	else
	{
		while (i++ < len)
			dsttemp[i - 1] = srctemp[i - 1];
	}
	return (dsttemp);
}
