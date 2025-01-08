/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:43:57 by vcaratti          #+#    #+#             */
/*   Updated: 2025/01/07 12:26:06 by vcaratti         ###   ########.fr       */
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

char	**list_to_arr(t_elist *head)
{
	char		**ret;
	int		i;
	int		len;
	t_elist	*current;

	if (!head)
		return (NULL);
	len = list_len(head);
	ret = malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	i = 0;
	current = head;
	while (current)
	{
		ret[i] = current->arg;
		current->arg = 0;
		i++;
		current = current->next;
	}
	ret[i] = 0;
	return (ret);
}


void	rev_free(char **arr, int i)
{
	while (i >= 0)
		free(arr[i--]);
}

char	**list_to_arr_dup(t_elist *head)
{
	char		**ret;
	int		i;
	int		len;
	t_elist	*current;

	if (!head)
		return (NULL);
	len = list_len(head);
	ret = malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	i = 0;
	current = head;
	while (current)
	{
		ret[i] = ft_strdup(current->arg);
		if (!ret[i])
			return (rev_free(ret, i - 1), NULL);
		i++;
		current = current->next;
	}
	ret[i] = 0;
	return (ret);
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
