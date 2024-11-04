/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:20:23 by vcaratti          #+#    #+#             */
/*   Updated: 2023/11/08 15:25:32 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		counter;
	char	*ret;

	if (!s || !f)
		return (NULL);
	counter = 0;
	while (s[counter])
		counter++;
	ret = (char *)malloc((counter + 1) * sizeof(char));
	if (ret == NULL)
		return (NULL);
	counter = 0;
	while (s[counter])
	{
		ret[counter] = f(counter, s[counter]);
		counter++;
	}
	ret[counter] = '\0';
	return (ret);
}
