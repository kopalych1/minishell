/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 10:53:11 by vcaratti          #+#    #+#             */
/*   Updated: 2023/11/23 14:39:08 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

	if (!dst && dstsize == 0)
		return (ft_strlen(src));
	if (dstsize <= ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	dst_len = ft_strlen((char *)dst);
	src_len = ft_strlen((char *)src);
	if ((dst_len >= dstsize) || dstsize == 0)
		return (src_len + dstsize);
	i = 0;
	j = dst_len;
	while (src[i] != '\0' && i < dstsize - dst_len - 1)
		dst[j++] = src[i++];
	dst[j] = '\0';
	return (dst_len + src_len);
}
