/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:52:38 by vcaratti          #+#    #+#             */
/*   Updated: 2024/12/23 13:46:16 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

int	open_outfiles(t_elist *outfiles)
{
	t_elist	*current;
	int	fd;

	current = outfiles;
	if (!current)
		return (-1);
	while (current->next)
	{
		fd = open(current->arg, O_WRONLY | O_CREAT, 0777);
		if (fd == -1)
			return (-2);// PERROR(NULL);
		close(fd);
		current = current->next;
	}
	if (current->mode != 'a')
		return (open(current->arg, O_WRONLY | O_CREAT | O_TRUNC, 0777)); // needs support for O_RDWR | O_APPEND
	fd = open(current->arg, O_RDWR | O_APPEND, 0777);
	if (fd == -1)
		fd = open(current->arg, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	return (fd);
}

int	open_infiles(t_elist *infiles)
{
	t_elist	*current;
	int	fd;

	current = infiles;
	if (!current)
		return (-1);//idk?
	while (current->next)
	{
		fd = open(current->arg, O_RDONLY, 0777);
		if (fd == -1)
			return (-2);// PERROR(NULL);
		close(fd);
		current = current->next;
	}
	fd = open(current->arg, O_RDONLY, 0777); // needs support for O_RDWR | O_APPEND
	return (fd);
}

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
		current = current->next;
	}
}
