/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:34:05 by vcaratti          #+#    #+#             */
/*   Updated: 2024/12/24 14:04:25 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

int	heredoc_routine(int fd, char *eof)
{
	char	*line;

	while (1)
	{
		line = readline(">");
		if (!line)
			return (1);
		if (!ft_strcmp(line, eof))//need to handle signal;
			break;
		if (fd != -1)
		{
			if (write(fd, line, ft_strlen(line)) == -1)
				return (1);
		}
		free(line);
		
	}
	close(fd);
	return (0);
}

int	heredoc(int fd, char *eof)
{
	int	child;
	int	ret;

	child = fork();
	if (child == -1)
		return (1);
	if (child == 0)
		heredoc_routine(fd, eof);
	waitpid(child, &ret, WCONTINUED);
	return (ret);
}
