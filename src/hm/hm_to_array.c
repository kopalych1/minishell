/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_to_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:54:06 by vcaratti          #+#    #+#             */
/*   Updated: 2025/01/13 14:14:06 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hashmap.h"

void	free_until(char	**arr, int i)
{
	while (--i >= 0)
		free(arr[i]);
	free(arr);
}

char	*join_key_content(t_hashmap_item *item)
{
	char	*left_str;
	char	*ret;

	left_str = ft_strjoin(item->key, "=");
	if (!left_str)
		return (NULL);
	ret = ft_strjoin(left_str, item->content);
	free(left_str);
	if (!ret)
		return (NULL);
	return (ret);
}

char **hm_to_array(t_hashmap *hm)
{
	size_t	i;
	char	**ret;

	ret = malloc(sizeof(char *) * (hm->length + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < hm->length)
	{
		ret[i] = join_key_content(hm->items + i);
		if (!ret[i])
			return (free_until(ret, i), NULL);
		i++;
	}
	ret[hm->length] = 0;
	return (ret);
}
