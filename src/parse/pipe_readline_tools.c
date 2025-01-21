/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_readline_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:34:05 by vcaratti          #+#    #+#             */
/*   Updated: 2025/01/21 12:12:27 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_interupt(int signum)
{
	if (signum == SIGINT || signum == 130)
	{
		if (signum == SIGINT)
			exit(3);
		printf("minishell: syntax error: unexpected end of file\n");
		exit(130);
	}
}

void	free_close_exit(char **arr, int fd, int ret)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	close(fd);
	exit(ret);
}

int	starts_with_pipe(char *str)
{
	size_t	i;

	i = -1;
	while (++i < ft_strlen(str))
	{
		if (ft_isspace(str[i]))
			continue ;
		else if (str[i] == '|')
			return (1);
		else
			return (0);
	}
	return (0);
}

int	ends_with_pipe(char *str)
{
	int	i;

	i = ft_strlen(str);
	while (--i)
	{
		if (ft_isspace(str[i]))
			continue ;
		else if (str[i] == '|')
			return (1);
		else
			return (0);
	}
	return (0);
}
