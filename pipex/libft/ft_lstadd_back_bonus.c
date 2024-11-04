/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:59:56 by vcaratti          #+#    #+#             */
/*   Updated: 2023/11/02 13:38:41 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (!lst || !(*lst))
	{
		*lst = new;
		return ;
	}
	if (!new)
		return ;
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}
