/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:53:50 by vcaratti          #+#    #+#             */
/*   Updated: 2023/11/02 13:40:28 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*current;
	int		counter;

	if (!lst)
		return (0);
	counter = 1;
	current = lst;
	while (current->next != NULL && current->next != lst)
	{
		current = current->next;
		counter++;
	}
	return (counter);
}
