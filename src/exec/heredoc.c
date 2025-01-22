/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:15:46 by vcaratti          #+#    #+#             */
/*   Updated: 2025/01/22 13:15:13 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

int	heredoc_check(t_elist **node, t_executor *exec)
{
	t_elist	*to_del;
	int		hd_ret;

	if (!(*node)->next && (*node)->mode == 'h')
	{
		if (pipe((exec->heredoc_p)) == -1)
			return (1);
		hd_ret = heredoc(exec->heredoc_p[1], (*node)->arg, exec->env_variables);
		if (hd_ret)
			return (hd_ret);
		if ((*node)->prev)
			(*node)->prev->mode = 'd';
	}
	else if ((*node)->mode == 'h')
	{
		hd_ret = heredoc(-1, (*node)->arg, exec->env_variables);
		if (hd_ret)
			return (hd_ret);
	}
	if ((*node)->mode == 'h')
		pop_hd_operator(&to_del, node);
	return (0);
}

int	init_heredocs(t_executor *exec_head)
{
	t_elist	*current;
	int		hd_ret;

	while (exec_head)
	{
		current = exec_head->infiles.next;
		while (current)
		{
			if (current->mode == 'h')
			{
				hd_ret = heredoc_check(&current, exec_head);
				if (hd_ret)
					return (hd_ret);
				exec_head->heredoc_p[1] = -1;
			}
			else
				current = current->next;
		}
		exec_head = exec_head->next;
	}
	return (0);
}

static int	route_hd_line(char **arr, t_hashmap *env, int fd)
{
	int	ret;

	ret = 0;
	if (!arr[0])
	{
		free(arr);
		exit(1);
	}
	if (fd != -1)
	{
		if (post_process_argv(&arr, 1, env) == -1)
			ret = 1;
		else if (write(fd, arr[0], ft_strlen(arr[0])) == -1)
			ret = 1;
	}
	free(arr[0]);
	free(arr);
	return (ret);
}

static void	heredoc_routine(int fd, char *eof, t_hashmap *env)
{
	char	*line;
	char	**arr;
	int		ret;

	signal(SIGINT, hd_handle_interupt);
	signal(SIGQUIT, hd_handle_interupt);
	ret = 0;
	while (1 && !ret)
	{
		arr = malloc(sizeof(char *));
		if (!arr)
			exit(1);
		line = readline(">");
		if (!line)
			hd_handle_interupt(130);
		if (!ft_strcmp(line, eof))
			break ;
		arr[0] = ft_strjoin(line, "\n");
		free(line);
		ret = route_hd_line(arr, env, fd);
	}
	close(fd);
	exit(ret);
}

int	heredoc(int fd, char *eof, t_hashmap *env)
{
	int			child;
	int			ret;
	extern int	g_exit_code;

	child = fork();
	if (child == -1)
		return (1);
	if (child == 0)
		heredoc_routine(fd, eof, env);
	close(fd);
	waitpid(child, &ret, WCONTINUED);
	if (ret == 256)
		g_exit_code = 2;
	if (ret == 256)
		return (2);
	return (0);
}
