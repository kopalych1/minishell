/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:05:03 by vcaratti          #+#    #+#             */
/*   Updated: 2024/11/04 12:58:40 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	child_fun(t_cmd cmds, int prev, int next, char **envp)
{
	if (prev != 0)
	{
		if (dup2(prev, 0) == -1)
			return (close(prev), close(next), -1);
		close(prev);
	}
	if (next != 0)
	{
		if (dup2(next, 1) == -1)
			return (close(next), -1);
		close(next);
	}
	execve(cmds.path, cmds.args, envp);
	return (0);
}

static int	run_child(t_cmd c, int prev, int next, char **envp)
{
	if (child_fun(c, prev, next, envp) < 0)
		return (-1);
	return (0);
}

int	child_routine(t_cmd cmd, t_pipex *d, int n)
{
	char	**argv;
	char	**envp;
	int		argc;

	argv = d->argv;
	envp = d->envp;
	argc = d->argc;
	if (n == 0 && n == get_nb_cmds(argv, argc) - 1)
		return (run_child(cmd, d->files[0], d->files[1], envp));
	if (n == 0)
	{
		if (run_child(cmd, d->files[0], d->pipes[1], envp) < 0)
			return (-1);
	}
	else if (n == get_nb_cmds(argv, argc) - 1)
	{
		if (run_child(cmd, d->pipes[(n - 1) * 2], d->files[1], envp) < 0)
			return (-1);
	}
	else if (run_child(cmd, d->pipes[(n - 1) * 2]
			, d->pipes[(n * 2) + 1], envp) < 0)
		return (-1);
	return (0);
}

int	open_pipes_children(int nb_pipes, t_pipex *data)
{
	int	n;

	data->pipes = malloc(sizeof(int) * (nb_pipes * 2));
	if (data->pipes == NULL)
		return (-1);
	data->children = malloc(sizeof(int) * (nb_pipes + 1));
	if (data->children == NULL)
		return (free(data->pipes), -1);
	n = 0;
	while (n < nb_pipes)
	{
		if (pipe(&(data->pipes[n * 2])) == -1)
			return (free(data->pipes), free(data->children), -1);
		n++;
	}
	return (0);
}
