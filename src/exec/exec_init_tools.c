/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:10:54 by vcaratti          #+#    #+#             */
/*   Updated: 2025/01/16 13:11:46 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

t_elist *list_pop(t_elist *node)
{
	if (!node->prev)
		return (NULL);
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	return (node);
}

int	pop_append(t_elist *args_head, t_elist *to_append)
{
	t_elist	*current;

	current = args_head->next;
	if (!current->next)
		return (1);//no infile/outfile specified
	if (has_special_c(current->next->arg))
		return (1);
	free_list_node(list_pop(args_head->next));
	list_append(to_append, list_pop(args_head->next));
	return (0);
}

int	list_init(t_elist *args_head, char **args)
{
	int	i;

	args_head->arg = 0;	
	args_head->next = 0;
	args_head->prev = 0;
	i = 0;
	while (args[i])
	{
		if (list_append_arg(args_head, args[i++]))
			return (1);//
	}
	if (i == 0)
		return (1);
	return (0);
}
