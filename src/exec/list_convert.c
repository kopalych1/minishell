/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_convert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:16:02 by vcaratti          #+#    #+#             */
/*   Updated: 2025/01/20 13:41:49 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

char	**list_to_arr(t_elist *head)
{
	char	**ret;
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

char	**list_to_arr_dup(t_elist *head)
{
	char	**ret;
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
