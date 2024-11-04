/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:56:14 by vcaratti          #+#    #+#             */
/*   Updated: 2024/11/04 13:03:26 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	free_cmds_e_ret(t_cmd *in, t_cmd *out, int error)
{
	int		i;

	(void)out;
	if (in->path != NULL)
		free(in->path);
	if (in->args != NULL)
	{
		i = 0;
		while (in->args[i])
			free(in->args[i++]);
		free(in->args);
	}
	return (error);
}

int	free_map_e_ret(char **arr, int error)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	return (error);
}

void	close_wait(t_pipex *data)
{
	int	n;
	int	nb_cmds;

	n = -1;
	nb_cmds = get_nb_cmds(data->argv, data->argc);
	close(data->files[0]);
	close(data->files[1]);
	while (++n < nb_cmds -1)
		waitpid(data->children[n], NULL, 0);
	n = -1;
	while (++n < nb_cmds -1)
		close(data->pipes[n]);
}

int	start_fork(int *childfd)
{
	*childfd = fork();
	return (*childfd);
}

int	open_files(char *infile, char *outfile, int *file_fds, int append)
{
	file_fds[0] = 0;
	file_fds[1] = 0;
	if (infile)
		file_fds[0] = open(infile, O_RDONLY);
	if (file_fds[0] == -1)
		perror(NULL);
	if (outfile && append)
		file_fds[1] = open(outfile, O_RDWR | O_APPEND, 0777);
	if (outfile && !append)
		file_fds[1] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_fds[1] == -1)
		perror(NULL);
	if (file_fds[0] < 0 && file_fds[1] < 0)
		return (-1);
	if (file_fds[0] < 0 && file_fds[1] >= 0)
		return (close(file_fds[1]), -1);
	if (file_fds[1] < 0 && file_fds[0] >= 0)
		return (close(file_fds[0]), -1);
	return (0);
}
