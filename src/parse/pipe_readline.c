/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:34:05 by vcaratti          #+#    #+#             */
/*   Updated: 2025/01/22 13:30:50 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"

int	check_line(char *line, char ***arr, int *stop)
{
	char	**new_arr;
	int		i;

	*stop = 1;
	if (starts_with_pipe(line))
	{
		ft_printf("minishell: syntax error near unexpected token '|'\n");
		return (free(line), free_nt_arr(*arr), exit(2), 2);
	}
	new_arr = (char **)malloc(sizeof(char *) * (ft_arr_len(*arr) + 2));
	if (!new_arr)
		return (free(line), free_nt_arr(*arr), exit(1), 1);
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

static int	get_new_line(char **line, char ***arr)
{
	int	stop;

	stop = 0;
	while (!stop)
	{
		*line = readline("pipe>");
		if (!(*line))
			return (1);
		while ((*line)[0] == '\0')
		{
			free(*line);
			*line = readline("pipe>");
			if (!(*line))
				return (1);
		}
		check_line(*line, arr, &stop);
	}
	return (0);
}

static void	pipe_readline_routine(int fd, t_hashmap *env)
{
	char	**arr;
	int		stop;
	char	*line;

	signal(SIGINT, handle_interupt);
	signal(SIGQUIT, handle_interupt);
	arr = NULL;
	if (get_new_line(&line, &arr))
		return (free_nt_arr(arr), handle_interupt(130));
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

//256:	malloc/write error
//512:	bad token
//768:	ctrl-C
//33280:ctrl-D
static void	set_exit_code(void)
{
	extern int	g_exit_code;

	if (g_exit_code == 256)
		g_exit_code = 1;
	if (g_exit_code == 512)
		g_exit_code = 2;
	if (g_exit_code == 768)
		g_exit_code = 130;
	if (g_exit_code == 33280)
		g_exit_code = 3;
}

char	*pipe_readline(t_hashmap *env)
{
	int			child;
	extern int	g_exit_code;
	int			pipes[2];
	char		*line;

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
		free(line);
	if (g_exit_code)
		line = NULL;
	return (set_exit_code(), line);
}
