/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 23:17:07 by akostian          #+#    #+#             */
/*   Updated: 2025/01/23 12:15:04 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hashmap.h"

int	hm_set(t_hashmap *hm, const char *key, void *elem, unsigned char do_free)
{
	t_hashmap_item	*old_items;
	ssize_t			key_index;

	if (!key)
		return (-1);
	key_index = hm_key_exists(hm, key);
	if (key_index != -1)
	{
		if (hm->items[key_index].do_free)
			free(hm->items[key_index].content);
		hm->items[key_index].content = elem;
		return (hm->items[key_index].do_free = do_free, 0);
	}
	old_items = hm->items;
	hm->items = ft_realloc(hm->items, sizeof(t_hashmap_item) * hm->length,
			sizeof(t_hashmap_item) * (hm->length + 1));
	if (!hm->items)
		return (hm->items = old_items, -1);
	hm->items[hm->length].key = ft_strdup(key);
	if (!hm->items[hm->length].key)
		return (-1);
	hm->items[hm->length].content = elem;
	return (hm->items[hm->length++].do_free = do_free, 0);
}
