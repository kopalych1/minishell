#include "../../include/exec.h"

static int	handle_pipe_sep(t_executor **p_current_exec
			, t_elist *args_head, t_hashmap *env_variables)
{
	t_executor	*current_exec;

	current_exec = *p_current_exec;
	if (!current_exec->exec_args.next 
		&& !current_exec->infiles.next && !current_exec->outfiles.next)
		return (2);//'|' token first, prints error
	if (create_exec(&(current_exec->next), current_exec, 0, env_variables))
		return (1);
	*p_current_exec = current_exec->next;
	free_list_node(list_pop(args_head->next));
	if (args_head->next == 0) // nothing after pipe
		return (1); //SHOULDNT BE ERROR, needs to wait for user command input, try it on bash
	return (0);
}

static int	parse_args(t_executor *exec_head, t_elist *args_head, t_hashmap *env_variables)
{
	t_executor	*current_exec;
	int		pipe_sep_ret;

	current_exec = exec_head;
	while (args_head->next)
	{
		if (has_special_c(args_head->next->arg))
		{
			if (fetch_redirect(args_head, current_exec))
				return (free_list(args_head), 1);//bad redirect
		}
		else if (ft_strcmp(args_head->next->arg, "|") == 0)
		{
			pipe_sep_ret = handle_pipe_sep(&current_exec, args_head, env_variables);
			if (pipe_sep_ret)
				return (free_list(args_head), pipe_sep_ret);
		}
		else
			list_append(&(current_exec->exec_args), list_pop(args_head->next));
	}
	return (0);
}

int	tokenise(char **args, t_executor **exec_head, t_hashmap *env_variables)
{
	t_elist	args_head;
	int	parse_ret;

	if (list_init(&args_head, args))
		return (free_list(&args_head), 2);
	if (create_exec(exec_head, 0, 0, env_variables))
		return (free_list(&args_head), 2);
	parse_ret = parse_args(*exec_head, &args_head, env_variables);
	free_list(&args_head);
	if (parse_ret == 2)
		return (write(1,"syntax error near unexpected token '|'\n", 39)
			,free_all(exec_head),1);
	else if (parse_ret)
		return (free_all(exec_head), 2);
	return (0);
}
