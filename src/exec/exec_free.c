/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:26:08 by vcaratti          #+#    #+#             */
/*   Updated: 2025/01/20 13:18:27 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

void	free_list(t_elist *head)
{
	t_elist	*current;
	t_elist	*next;

	current = head->next;
	while (current)
	{
		next = current->next;
		free(current->arg);
		free(current);
		current = next;
	}
	head->next = 0;
}

void	free_nt_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i] != 0)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_all(t_executor **head)
{
	t_executor	*current;
	t_executor	*next;

	current = *head;
	while (current)
	{
		next = current->next;
		if (current->infiles.next)
			free_list(&(current->infiles));
		if (current->outfiles.next)
			free_list(&(current->outfiles));
		if (current->exec_args.next)
			free_list(&(current->exec_args));
		if (current->cmd.args)
			free_nt_arr(current->cmd.args);
		if (current->cmd.path)
			free(current->cmd.path);
		free(current);
		*head = NULL;
		current = next;
	}
}

int	free_and_ret(char **to_free, int ret)
{
	int	i;

	i = 0;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
	return (ret);
}

void	free_list_node(t_elist *list)
{
	free(list->arg);
	free(list);
}
