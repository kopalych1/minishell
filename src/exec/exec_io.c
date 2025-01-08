/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:52:38 by vcaratti          #+#    #+#             */
/*   Updated: 2024/12/27 11:20:43 by vcaratti         ###   ########.fr       */
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
		//fd = exec->heredoc_p[0];
		//exec->heredoc_p[0] = -1;
	}
	return (fd);
}
/*
void	close_all_except(t_executor *exec)
{
	t_executor	*current;

	current = exec;
	while (current->prev != 0)
		current = current->prev;
	while (current)
	{
		if (current == exec)
			continue;
		if (current->fds[0] > -1)
			close(current->fds[0]);
		if (current->fds[1] > -1)
			close(current->fds[1]);
		if (current->pipes[0] > -1)
			close(current->pipes[0]);
		if (current->pipes[1] > -1)
			close(current->pipes[1]);
		if (current->heredoc_p[0] > -1)
			close(current->heredoc_p[0]);
		if (current->heredoc_p[1] > -1)
			close(current->heredoc_p[1]);
		current = current->next;
	}
}*/
