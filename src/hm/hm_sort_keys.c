/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_sort_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:18:24 by akostian          #+#    #+#             */
/*   Updated: 2024/11/12 13:19:21 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hashmap.h"

void	hm_sort_keys(t_hashmap *hm)
{
	size_t			i;
	size_t			j;
	t_hashmap_item	tmp;

	i = 0;
	while (i < hm->length)
	{
		j = i;
		while (j < hm->length)
		{
			if (ft_strcmp(hm->items[i].key, hm->items[j].key) > 0)
			{
				tmp = hm->items[i];
				hm->items[i] = hm->items[j];
				hm->items[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
