/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:48:05 by vcaratti          #+#    #+#             */
/*   Updated: 2023/11/08 16:08:39 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ret;
	size_t			i;

	if ((size != 0) && (count * size) / size != count)
		return (NULL);
	ret = malloc(size * count);
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < count * size)
		ret[i++] = 0;
	return ((void *)ret);
}
