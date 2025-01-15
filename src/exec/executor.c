/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:37:53 by vcaratti          #+#    #+#             */
/*   Updated: 2025/01/15 15:14:19 by vcaratti         ###   ########.fr       */
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
{
		//printf("in cmd: %s\n", exec->cmd.path);fflush(stdout);
		exec->fds[1] = open_outfiles(exec);
		exec->fds[0] = open_infiles(exec);
		if (exec->bad_command == 1)
		{
			close_all(exec);
			ft_printf("Command not found\n");fflush(stdout);
			exit(127);
		}
		if (exec->fds[0] == -2 || exec->fds[1] == -2)
			return (1);//
		if (exec->fds[0] == -1)
		{	if (exec->heredoc_p[0] > -1)
			{
				if (dup2(exec->heredoc_p[0], 0))
					return (1);
			}	
			else if (pipe_dup(exec->pipes[0], 0))
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
		if ((!exec->cmd.path && !exec->exec_args.next))//just redirects
			exit(0);
		if (!exec->cmd.path && exec->exec_args.next)//builtin
			exit(builtin_routine(exec));
		execve(exec->cmd.path, exec->cmd.args, exec->envp);
		return (0);
}

void	ignore_signal(int signum)
{
	(void)signum;
}

int	start_pipes(t_executor **exec_head)
{
	t_executor	*current;
	int		cmd_init_ret;
	int		hd_ret;

	signal(SIGINT, ignore_signal);
	signal(SIGKILL, ignore_signal);
	hd_ret = init_heredocs(*exec_head);
	if (hd_ret == 1)
		return (1);
	else if (hd_ret == 2)
		return (0);
	cmd_init_ret = init_cmd_args(*exec_head);
	//printf("cmd ret: %d\n", cmd_init_ret); fflush(stdout);
	if (cmd_init_ret == 1) //PROBLEM WITH BUILTINS
		return (1);//free t_cmd? gotta watch out for copies and non-malloced
	if (cmd_init_ret == 2)
		return (0);//bad command
	if (init_children_pipes(*exec_head))
		return (1);//
	current = *exec_head;
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
		if (current->heredoc_p[0] > -1)
			close(current->heredoc_p[0]);
		if (current->heredoc_p[1] > -1)
			close(current->heredoc_p[1]);
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

int	handle_pipe_sep(t_executor **p_current_exec, t_elist *args_head, char **envp/*tbr*/, t_hashmap *env_variables)
{
	t_executor	*current_exec;

	current_exec = *p_current_exec;
	if (!current_exec->exec_args.next && !current_exec->infiles.next && !current_exec->outfiles.next)
		return (2);//'|' token first, prints error
	if (create_exec(&(current_exec->next), current_exec, 0, envp, env_variables))
		return (1);
	*p_current_exec = current_exec->next;
	free_list_node(list_pop(args_head->next));
	if (args_head->next == 0) // nothing after pipe
		return (1); //SHOULDNT BE ERROR, needs to wait for user command input, try it on bash
	return (0);
}

int	parse_args(t_executor *exec_head, t_elist *args_head, char **envp/*to be removed*/, t_hashmap *env_variables)
{
	t_executor	*current_exec;
	int		pipe_sep_ret;

	current_exec = exec_head;
	while (args_head->next)
	{
		if (has_special_c(args_head->next->arg))
		{
			if (fetch_redirect(args_head, current_exec))
				return (free_list(args_head), free_all(exec_head), 1);//bad redirect
		}
		else if (ft_strcmp(args_head->next->arg, "|") == 0)
		{
			pipe_sep_ret = handle_pipe_sep(&current_exec, args_head, envp, env_variables);
			if (pipe_sep_ret)
				return (free_list(args_head), free_all(exec_head), pipe_sep_ret);
		}
		else
			list_append(&(current_exec->exec_args), list_pop(args_head->next));
	}
	return (0);
}

int	executor(char **args, char **envp, t_hashmap *env_variables, int *exec_ret)
{ //STILL NEED TO CHECK FOR EXPORT AND ENV
	t_elist		args_head;
	t_executor	*exec_head;
	int		parse_ret;

	if (list_init(&args_head, args))
		return (free_list(&args_head), 1);//?
	if (create_exec(&exec_head, 0, 0, envp, env_variables))
		return (free_list(&args_head), 1);//?
	parse_ret = parse_args(exec_head, &args_head, envp, env_variables);
	free_list(&args_head);
	if (parse_ret == 2)
		return (write(1,"syntax error near unexpected token '|'\n", 39),free_all(exec_head), 0); //for unexpected token
	else if (parse_ret)
		return (free_all(exec_head), 1);
	if (start_pipes(&exec_head))
		return (free_all(exec_head), 1);//free
	*exec_ret = close_wait(exec_head);
	if (is_builtin(exec_head) && !exec_head->next)
	{
		if (!ft_strcmp(exec_head->exec_args.next->arg, "exit"))
		{
			free_all(exec_head);
			exit(0);//?
		}
	}
	free_all(exec_head);
	return (0);	
}

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



