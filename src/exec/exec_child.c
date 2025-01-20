/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:15:05 by vcaratti          #+#    #+#             */
/*   Updated: 2025/01/20 13:33:17 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

void	close_all(t_executor *exec)
{
	while (exec->prev)
		exec = exec->prev;
	while (exec)
	{
		if (exec->fds[0] != -1)
			close(exec->fds[0]);
		if (exec->fds[1] != -1)
			close(exec->fds[1]);
		if (exec->pipes[0] != -1)
			close(exec->pipes[0]);
		if (exec->pipes[1] != -1)
			close(exec->pipes[1]);
		if (exec->heredoc_p[0] != -1)
			close(exec->heredoc_p[0]);
		if (exec->heredoc_p[1] != -1)
			close(exec->heredoc_p[1]);
		exec = exec->next;
	}
}

int	pipe_dup(int pipe_fd, int fd)
{
	if (pipe_fd != -1)
	{
		if (dup2(pipe_fd, fd) == -1)
			return (1);
	}
	return (0);
}

int	handle_dups(t_executor *exec)
{
	if (exec->fds[0] == -2 || exec->fds[1] == -2)
		return (1);
	if (exec->fds[0] == -1)
	{
		if (exec->heredoc_p[0] > -1)
		{
			if (dup2(exec->heredoc_p[0], 0))
				return (1);
		}
		else if (pipe_dup(exec->pipes[0], 0))
			return (1);
	}
	else if (dup2(exec->fds[0], 0) == -1)
		return (3);
	if (exec->fds[1] == -1)
	{
		if (pipe_dup(exec->pipes[1], 1))
			return (1);
	}
	else if (dup2(exec->fds[1], 1) == -1)
		return (5);
	close_all(exec);
	return (0);
}

int	exec_routine(t_executor *exec)
{
	int	pipe_dup_ret;

	exec->fds[1] = open_outfiles(exec);
	exec->fds[0] = open_infiles(exec);
	if (exec->bad_command == 1)
	{
		close_all(exec);
		ft_printf("Command not found\n");
		exit(127);
	}
	pipe_dup_ret = handle_dups(exec);
	if (pipe_dup_ret)
		return (pipe_dup_ret);
	if ((!exec->cmd.path && !exec->exec_args.next))
		exit(0);
	if (!exec->cmd.path && exec->exec_args.next)
		exit(builtin_routine(exec));
	execve(exec->cmd.path, exec->cmd.args, exec->envp);
	return (0);
}
