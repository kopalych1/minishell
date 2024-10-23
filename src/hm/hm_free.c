/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 04:10:45 by akostian          #+#    #+#             */
/*   Updated: 2024/10/23 16:58:40 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hashmap.h"

void	hm_free(t_hashmap *hm)
{
	size_t	i;

	i = 0;
	while (i < hm->length)
	{
		free(hm->items[i].key);
		if (hm->items[i].do_free)
			free(hm->items[i].content);
		i++;
	}
	free(hm->items);
}
