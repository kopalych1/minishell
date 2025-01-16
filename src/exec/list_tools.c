/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:43:57 by vcaratti          #+#    #+#             */
/*   Updated: 2025/01/16 13:35:41 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

int	list_len(t_elist *head)
{
	t_elist *current;
	int	i;

	current = head;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}


void	rev_free(char **arr, int i)
{
	while (i >= 0)
		free(arr[i--]);
}

int	list_append_arg(t_elist *lst, char *arg)
{
	t_elist	*current;

	current = lst;
	while (current->next != 0)
		current = current->next;
	current->next = (t_elist *)malloc(sizeof(t_elist));
	if (!current->next)
		return (1); // free;
	current->next->prev = current;
	current->next->next = 0;
	current->next->mode = 0;
	current->next->arg = ft_strdup(arg); //if og is dynamic or static;
	if (!current->next->arg)
		return (1);
	return (0);
}

void	list_append(t_elist *lst, t_elist *node)
{
	t_elist	*current;

	current = lst;
	while (current->next)
		current = current->next;
	current->next = node;
	node->prev = current;
	node->next = 0;
}
