/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:55:00 by akostian          #+#    #+#             */
/*   Updated: 2024/10/23 16:58:29 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hashmap.h"

void	hm_init(t_hashmap *hm)
{
	hm->items = NULL;
	hm->length = 0;
	hm->get = hm_get;
	hm->set = hm_set;
	hm->free = hm_free;
}
