/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:20:04 by vcaratti          #+#    #+#             */
/*   Updated: 2023/11/24 13:21:18 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i++])
			return (1);
	}
	return (0);
}

static char	*create_empty_str(void)
{
	char	*ret;

	ret = (char *)malloc(1);
	if (ret == NULL)
		return (NULL);
	ret[0] = '\0';
	return (ret);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		end;
	int		start;
	char	*ret;
	size_t	counter;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (is_in_set(s1[start], set) == 1)
		start++;
	while (is_in_set(s1[end], set) == 1)
		end--;
	if (end < start)
		return (create_empty_str());
	ret = (char *)malloc((end - start + 2) * sizeof(char));
	if (ret == NULL)
		return (NULL);
	counter = 0;
	while (start <= end)
		ret[counter++] = s1[start++];
	ret[counter] = '\0';
	return (ret);
}
