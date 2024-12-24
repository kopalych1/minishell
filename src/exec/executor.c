/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:37:53 by vcaratti          #+#    #+#             */
/*   Updated: 2024/12/24 14:35:05 by vcaratti         ###   ########.fr       */
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

int	exec_routine(t_executor *exec)
{//NEED TO CHECK FOR HERDOC PIPE
		exec->fds[1] = open_outfiles(exec->outfiles.next);
		exec->fds[0] = open_infiles(exec->infiles.next);
		if (exec->fds[0] == -2 || exec->fds[1] == -2)
			return (1);//
		if (exec->fds[0] == -1)
		{
			if (pipe_dup(exec->pipes[0], 0))
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
		execve(exec->cmd.path, exec->cmd.args, exec->envp);
		return (0);
}

int	heredoc_check(t_elist **node, t_executor *exec)
{
	t_elist	*to_del;

	if (!(*node)->next && (*node)->mode == 'h')
	{
		if (pipe(&(exec->heredoc_p)) ==  -1)
			return (1);
		if (heredoc(exec->heredoc_p[1], (*node)->arg))
			return (1);
		if ((*node)->prev)
			(*node)->prev->mode = 'd';
	}
	else if ((*node)->mode == 'h')
	{
		if (heredoc(-1, (*node)->arg))
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

int	init_heredoc(t_executor *exec_head)
{
	t_elist	*current;
	t_elist *to_del;

	while (exec_head)
	{
		current = exec_head->infiles.next;
		while (current)
		{
			if (current->mode == 'h')
			{
				if (heredoc_check(current, exec_head))
					return (1);
			}
			else
				current = current->next;
		}
		exec_head = exec_head->next;
	}
	return (0);
}

int	start_pipes(t_executor *exec_head)
{
	t_executor	*current;

	if (init_cmd_args(exec_head))
		return (1);//free t_cmd? gotta watch out for copies and non-malloced
	if (init_children_pipes(exec_head))
		return (1);//
	if (init_heredoc(exec_head))
		return (1);
	if (builtin_routine(exec_head))
		return (1);
	current = exec_head;
	while (current)
	{
		current->fid = fork();
		if (current->fid == -1)
			return (3);///
		if (current->fid == 0)
		{
			if (exec_routine(current))
				exit(1);
		}
		current = current->next;
	}
	return (0);
}
/*
void	print_list(t_elist *lst_head)
{
	t_elist *current = lst_head->next;
	printf("printing list...\n");
	while (current)
	{
		printf("\t%s\n", current->arg);
		current = current->next;
	}
}

void	print_data(t_executor *exec_head)
{
	t_executor *current_exec = exec_head;
	int	counter = 0;
	while (current_exec)
	{
		printf("EXEC %d\n", counter++);
		printf("\texecutor infiles:\n");
		t_elist *current_i = current_exec->infiles.next;
		while (current_i)
		{
			printf("\t\t->%s<-\n", current_i->arg);
			current_i = current_i->next;
		}
		printf("\texecutor outfiles:\n");
		current_i = current_exec->outfiles.next;
		while (current_i)
		{
			printf("\t\t->%s<-\n", current_i->arg);
			current_i = current_i->next;
		}
		//return (0);
		printf("\texecutor args:\n");
		current_i = current_exec->exec_args.next;
		while (current_i)
		{
			printf("\t\t->%s<-\n", current_i->arg);
			current_i = current_i->next;
		}
		current_exec = current_exec->next;
	}
}
*/
int	close_wait(t_executor *exec_head)
{
	t_executor	*current;
	int		ret;

	current = exec_head;
	ret = 0;
	while (current)
	{
		if (current->fds[0] > 1)
			close(current->fds[0]);
		if (current->fds[1] > 1)
			close(current->fds[1]);
		if (current->pipes[0] > 1)
			close(current->pipes[0]);
		if (current->pipes[1] > 1)
			close(current->pipes[1]);
		current = current->next;
	}
	current = exec_head;
	while (current)
	{
		waitpid(current->fid, &ret, WCONTINUED);//return values
		current = current->next;
	}
	return (ret);
}

int	executor(char **args, char **envp)
{
	//check for | |
	int		ret;
	t_elist		args_head;
	t_executor	*exec_head;
	t_executor	*current_exec;

	if (list_init(&args_head, args))
		return (free_list(&args_head), 1);//?
	if (create_exec(&exec_head, 0, 0, envp))
		return (free_list(&args_head), 1);//?
	current_exec = exec_head;
	while (args_head.next)
	{
		if (has_special_c(args_head.next->arg))
		{
			//printf("#has special c#\n");fflush(stdout);
			if (fetch_redirect(&args_head, current_exec))
				return (free_list(&args_head), free_all(exec_head), 1);//bad redirect
		}
		else if (ft_strcmp(args_head.next->arg, "|") == 0)
		{
			//print_list(&args_head);
			if (args_head.next->prev == 0 && current_exec->infiles.next == 0 && current_exec->outfiles.next == 0)
				return (free_list(&args_head), free_all(exec_head), 1);//pipe is first with no redirects//check is still works
			if (create_exec(&(current_exec->next), current_exec, 0, envp))
				return (free_list(&args_head), free_all(exec_head), 1);
			current_exec = current_exec->next;
			free_list_node(list_pop(args_head.next));
			if (args_head.next == 0) // nothing after pipe
				return (free_all(exec_head), 1); //SHOULDNT BE ERROR, needs to wait for user command input, try it on bash
			//print_list(&args_head);
		}
		else
		{
			t_elist *temp = list_pop(args_head.next);
			list_append(&(current_exec->exec_args), temp/*list_pop(args_head.next)*/);
		}
	}
	if (start_pipes(exec_head))
		return (/*printf("START_PIPE FAILURE: %d\n", ret),*/ free_all(exec_head), 1);//free
	ret = close_wait(exec_head);
	free_all(exec_head);
	return (ret);	
}

//STILL NEEDS: >> (APPEND MODE)
/*
int main(int argc, char **argv, char **envp)
{
	char	**tmp = malloc(sizeof(char *) * argc);

	int	i = 1;
	while (i < argc)
	{
		tmp[i-1] = argv[i];
		i++;
	}
	tmp[i - 1] = 0;
	printf("input:");
	i = 0;
	while (tmp[i])
		printf(" >%s<", tmp[i++]);
	printf("\n");
	printf("executor: %d", executor(tmp, envp));
}

*/



