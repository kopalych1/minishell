/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:22:43 by vcaratti          #+#    #+#             */
/*   Updated: 2023/11/23 14:44:15 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;
	unsigned int	counter;

	counter = 0;
	if (s == NULL)
		return (NULL);
	if ((unsigned int)ft_strlen((char *)s) < start)
		return (ft_strdup(""));
	while (s[counter + start] && counter < len)
		counter++;
	res = (char *)malloc((counter + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	counter = 0;
	while (s[start] && counter < len)
		res[counter++] = s[start++];
	res[counter] = '\0';
	return (res);
}
