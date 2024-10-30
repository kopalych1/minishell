/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 23:17:07 by akostian          #+#    #+#             */
/*   Updated: 2024/10/24 20:52:39 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hashmap.h"

static void	free_hm_n(t_hashmap *hm, size_t i)
{
	free(hm->items[i].key);
	if (hm->items[i].do_free)
		free(hm->items[i].content);
	while (i--)
	{
		free(hm->items[i].key);
		if (hm->items[i].do_free)
			free(hm->items[i].content);
	}
}

ssize_t	hm_key_exists(t_hashmap *hm, const char *key)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < hm->length)
	{
		j = 0;
		while ((hm->items[i].key[j] == key[j])
			&& hm->items[i].key[j] && key[j])
			j++;
		if ((!hm->items[i].key[j]) && (!key[j]))
			return (i);
		i++;
	}
	return (-1);
}

int	hm_copy(t_hashmap *hm, t_hashmap_item *old_items)
{
	size_t	i;

	i = 0;
	while (i < hm->length)
	{
		hm->items[i].key = ft_strdup(old_items[i].key);
		hm->items[i].content = old_items[i].content;
		hm->items[i].do_free = old_items[i].do_free;
		if (!hm->items[i].key)
			return (
				free(old_items[i].key), free(old_items), free_hm_n(hm, i), -1
			);
		free(old_items[i].key);
		i++;
	}
	return (0);
}

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
	hm->items = malloc(sizeof(t_hashmap_item) * (hm->length + 1));
	if (!hm->items)
		return (-1);
	if (hm_copy(hm, old_items) == -1)
		return (-1);
	free(old_items);
	hm->items[hm->length].key = ft_strdup(key);
	if (!hm->items[hm->length].key)
		return (free_hm_n(hm, hm->length), -1);
	hm->items[hm->length].content = elem;
	return (hm->items[hm->length++].do_free = do_free, 0);
}
