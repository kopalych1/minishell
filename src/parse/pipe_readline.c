/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:34:05 by vcaratti          #+#    #+#             */
/*   Updated: 2025/01/15 15:15:06 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"

static void	handle_interupt(int signum)
{
	if (signum == SIGINT || signum == 130)
	{
		if (signum == SIGINT)
			exit(1);
		printf("minishell: syntax error: unexpected end of file\n");
		exit(130); // return code, needs to be in global?
	}
}

static void	free_close_exit(char **arr, int fd, int ret)
{
	free(arr[0]);
	free(arr);
	close(fd);
	exit(ret);
}

static void	pipe_readline_routine(int fd, t_hashmap *env)
{
	char	**arr;
	int	ret;

	signal(SIGINT, handle_interupt);
	signal(SIGQUIT, handle_interupt);
	arr = malloc(sizeof(char *));
	if (!arr)
		exit(1);
	arr[0] = readline(">");
	if (!arr[0])
		handle_interupt(130);
	if (!arr[0])
	{
		free(arr);
		exit(1);
	}
	ret = 0;
	if (post_process_argv(&arr, 1, env) == -1)
		ret = 1;
	else if (write(fd, arr[0], ft_strlen(arr[0])) == -1)
		ret = 1;
	free_close_exit(arr, fd, ret);
}

char	*pipe_readline(t_hashmap *env)
{
	int	child;
	extern int	g_exit_code;
	int	pipes[2];
	char	*line;

	g_exit_code = 0;
	if (pipe(pipes) == -1)
		return (NULL);
	child = fork();
	if (child == -1)
		return (NULL);
	if (child == 0)
		pipe_readline_routine(pipes[1], env);
	waitpid(child, &g_exit_code, WCONTINUED);
	close(pipes[1]);
	line = get_next_line(pipes[0]);
	if (g_exit_code)
		line = NULL;
	if (g_exit_code == 256) // ctrl-C
		g_exit_code = 130;
	if (g_exit_code == 33280) // ctrl-D
		g_exit_code = 0;
	return (line);
}
