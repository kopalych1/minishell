/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 18:31:37 by akostian          #+#    #+#             */
/*   Updated: 2024/11/06 05:08:08 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hashmap.h"

int	hm_delete(t_hashmap *hm, const char *key)
{
	const ssize_t	key_index = hm_key_exists(hm, key);
	size_t			i;

	if (key_index == -1)
		return (1);
	if (hm->items[key_index].do_free)
		free(hm->items[key_index].content);
	free(hm->items[key_index].key);
	hm->length--;
	i = key_index;
	while (i < hm->length)
	{
		hm->items[i] = hm->items[i + 1];
		i++;
	}
	return (0);
}
