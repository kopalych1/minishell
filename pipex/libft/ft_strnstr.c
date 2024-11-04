/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:09:43 by vcaratti          #+#    #+#             */
/*   Updated: 2024/07/08 11:51:24 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if ((!haystack || !needle) && !len)
		return (NULL);
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	i = 0;
	while (i < len && (haystack[i] != '\0'))
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (needle[j] == haystack[i + j] && needle[j]
				&& (i + j) < len)
				j++;
			if (needle[j] == 0 && j != 0)
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (0);
}
