/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:22:21 by vcaratti          #+#    #+#             */
/*   Updated: 2023/11/08 15:27:59 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_clean(t_list *first, void (*del)(void *), void *content)
{
	ft_lstclear(&first, del);
	del(content);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*current_n;
	t_list	*first_n;
	void	*content_n;

	if (!lst || !f || !del)
		return (NULL);
	first_n = NULL;
	current = lst;
	while (current != NULL)
	{
		content_n = f(current->content);
		current_n = ft_lstnew(content_n);
		if (current_n == NULL)
			return (ft_clean(first_n, del, content_n));
		if (first_n == NULL)
			first_n = current_n;
		else
			ft_lstadd_back(&first_n, current_n);
		current = current->next;
	}
	return (first_n);
}
