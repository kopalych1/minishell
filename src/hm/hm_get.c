/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:45:26 by akostian          #+#    #+#             */
/*   Updated: 2024/10/23 16:58:36 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hashmap.h"

void	*hm_get(t_hashmap *hm, const char *key)
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
			return (hm->items[i].content);
		i++;
	}
	return (NULL);
}
