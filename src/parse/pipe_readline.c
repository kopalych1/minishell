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
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	close(fd);
	exit(ret);
}

int	starts_with_pipe(char  *str)
{
	size_t	i;

	i = -1;
	while (++i < ft_strlen(str))
	{
		if (ft_isspace(str[i]))
			continue;
		else if(str[i] == '|')
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
			continue;
		else if (str[i] == '|')
			return (1);
		else
			return (0);
	}
	return (0);
}

int	check_line(char *line, char ***arr, int *stop)
{
	char	**new_arr;
	int	i;

	*stop = 1;
	if (starts_with_pipe(line))
	{
		ft_printf("minishell: syntax error near unexpected token '|'\n");
		return (free(line), free_nt_arr(*arr), 1);
	}
	new_arr = (char **)malloc(sizeof(char *) * (ft_arr_len(*arr) + 2));
	if (!new_arr)
		return (free(line), free_nt_arr(*arr), 1);
	i = -1;
	while (++i < ft_arr_len(*arr))
		new_arr[i] = (*arr)[i];
	new_arr[i++] = line;
	new_arr[i] = 0;
	free(*arr);
	*arr = new_arr;
	if (ends_with_pipe(line))
		*stop = 0;
	return (0);
}

static void	pipe_readline_routine(int fd, t_hashmap *env)
{
	char	**arr;
	int	stop;
	char	*line;

	signal(SIGINT, handle_interupt);
	signal(SIGQUIT, handle_interupt);
	arr = NULL;
	stop = 0;
	while (!stop)
	{
		line = readline(">");
		if (!line)
		{
			free_nt_arr(arr);
			handle_interupt(130);
		}
		if (check_line(line, &arr, &stop))
			exit(1);
	}
	if (post_process_argv(&arr, ft_arr_len(arr), env) == -1)
		free_close_exit(arr, fd, 1);
	else
	{
		stop = 0;
		while (arr[stop])
		{
			if (write(fd, arr[stop], ft_strlen(arr[stop])) == -1)
				free_close_exit(arr, fd, 1);
			stop++;
		}
	}
	free_close_exit(arr, fd, 0);
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
