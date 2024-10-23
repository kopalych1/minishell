/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:28:22 by akostian          #+#    #+#             */
/*   Updated: 2024/10/23 16:59:07 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHMAP_H
# define HASHMAP_H

# include "../libft/include/libft.h"

typedef struct s_hashmap_item
{
	char			*key;
	void			*content;
	unsigned char	do_free;
}	t_hashmap_item;

typedef struct s_hashmap
{
	t_hashmap_item		*items;
	size_t				length;
	void				(*hm_init)(
			struct s_hashmap *hm
			);
	void				*(*get)(
			struct s_hashmap *hm,
			const char *key
			);
	int					(*set)(
			struct s_hashmap *hm,
			const char *key,
			void *elem,
			unsigned char do_free
			);
	void				(*free)(
			struct s_hashmap *hm
			);
}	t_hashmap;

void		hm_init(t_hashmap *hm);
void		*hm_get(t_hashmap *hm, const char *key);
int			hm_set(
				t_hashmap *hm,
				const char *key,
				void *elem,
				unsigned char do_free
				);
void		hm_free(t_hashmap *hm);

#endif