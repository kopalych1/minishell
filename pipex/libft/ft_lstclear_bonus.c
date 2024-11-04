/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:05:46 by vcaratti          #+#    #+#             */
/*   Updated: 2023/11/08 15:27:37 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	if (!lst || *lst == NULL || !del)
		return ;
	current = *lst;
	while (current->next != NULL)
	{
		next = current->next;
		del(current->content);
		free(current);
		current = next;
	}
	del(current->content);
	free(current);
	*lst = NULL;
}
