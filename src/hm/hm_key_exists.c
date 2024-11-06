/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_key_exists.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 05:09:19 by akostian          #+#    #+#             */
/*   Updated: 2024/11/06 05:15:16 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hashmap.h"

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
