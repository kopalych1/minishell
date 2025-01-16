/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:52:38 by vcaratti          #+#    #+#             */
/*   Updated: 2025/01/16 13:15:26 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

int	open_outfiles(t_executor *exec)
{
	t_elist	*current;
	int	fd;

	current = exec->outfiles.next;
	if (!current)
		return (-1);
	while (current->next)
	{
		fd = open(current->arg, O_WRONLY | O_CREAT, 0777);
		if (fd == -1)
			return (perror(NULL), -2);
		close(fd);
		current = current->next;
	}
	if (current->mode != 'a')
		return (open(current->arg, O_WRONLY | O_CREAT | O_TRUNC, 0777));
	fd = open(current->arg, O_RDWR | O_APPEND, 0777);
	if (fd == -1)
		fd = open(current->arg, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (perror(NULL), -2);
	return (fd);
}

int	open_infiles(t_executor *exec)
{
	t_elist	*current;
	int	fd;

	current = exec->infiles.next;
	if (!current)
		return (-1);
	while (current->next)
	{
		fd = open(current->arg, O_RDONLY, 0777);
		if (fd == -1)
			return (perror(NULL), -2);
		close(fd);
		current = current->next;
	}
	fd = open(current->arg, O_RDONLY, 0777);
	if (fd == -1)
		return (perror(NULL), -2);
	if (current->mode == 'd')
	{
		close(fd);
		return (-1);
	}
	return (fd);
}
