/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:34:05 by vcaratti          #+#    #+#             */
/*   Updated: 2025/01/13 14:51:43 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

int	heredoc_check(t_elist **node, t_executor *exec)
{
	t_elist	*to_del;

	if (!(*node)->next && (*node)->mode == 'h')
	{
		if (pipe((exec->heredoc_p)) ==  -1)
			return (1);
		if (heredoc(exec->heredoc_p[1], (*node)->arg, exec->env_variables))
			return (1);
		if ((*node)->prev)
			(*node)->prev->mode = 'd';
	}
	else if ((*node)->mode == 'h')
	{
		if (heredoc(-1, (*node)->arg, exec->env_variables))
			return (1);
	}
	if ((*node)->mode == 'h')
	{
		to_del = (*node);
		(*node) = to_del->next;
		free_list_node(list_pop(to_del));
	}
	return (0);
}

int	init_heredocs(t_executor *exec_head)
{
	t_elist	*current;

	while (exec_head)
	{
		current = exec_head->infiles.next;
		while (current)
		{
			if (current->mode == 'h')
			{
				if (heredoc_check(&current, exec_head))
					return (1);
				exec_head->heredoc_p[1] = -1;
			}
			else
				current = current->next;
		}
		exec_head = exec_head->next;
	}
	return (0);
}

void	handle_interupt(int signum)
{
	if (signum == SIGINT || signum == 130)
	{
		//ft_printf("\n");
		//rl_replace_line("", 0);
		//rl_on_new_line();
		//rl_redisplay();
		//printf("wut?");fflush(stdout);
		if (signum == SIGINT)
			exit(0);
		exit(130); // return code, needs to be in global?
	}
}

void	heredoc_routine(int fd, char *eof, t_hashmap *env)
{
	char	*line;
	char	**arr;
	int	ret;

	signal(SIGINT, handle_interupt);
	signal(SIGQUIT, handle_interupt);
	while (1)
	{
		arr = malloc(sizeof(char *));
		if (!arr)
			exit(1);
		line = readline(">");
		if (!line)
			handle_interupt(130);
		if (!ft_strcmp(line, eof))
			break;
		arr[0] = ft_strjoin(line, "\n");
		free(line);
		if (!arr[0])
		{
			free(arr);
			exit(1);
		}
		ret = 0;
		if (fd != -1)
		{	
			if (post_process_argv(&arr, 1, env) == -1)
				ret = 1;
			else if (write(fd, arr[0], ft_strlen(arr[0])) == -1)
				ret = 1;
		}
		free(arr[0]);
		free(arr);
	}
	close(fd);
	exit(ret);
}

int	heredoc(int fd, char *eof, t_hashmap *env)
{
	int	child;
	int	ret;

	child = fork();
	if (child == -1)
		return (1);
	if (child == 0)
		heredoc_routine(fd, eof, env);
	close(fd);
	waitpid(child, &ret, WCONTINUED);
	//RET IS FOR GLOBAL, NEED TO IMPL THIS
	return (0);
}
