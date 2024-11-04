/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:03:51 by vcaratti          #+#    #+#             */
/*   Updated: 2023/11/23 14:37:15 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		counter;
	size_t	len;
	char	*ret;

	if (!s1 || !s2)
		return (NULL);
	len = 0;
	len += ft_strlen(s1) + ft_strlen(s2);
	ret = (char *)malloc((len + 1) * sizeof(char));
	if (ret == NULL)
		return (NULL);
	counter = 0;
	len = 0;
	while (s1[counter])
		ret[len++] = s1[counter++];
	counter = 0;
	while (s2[counter])
		ret[len++] = s2[counter++];
	ret[len] = '\0';
	return (ret);
}
