/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:43:03 by vcaratti          #+#    #+#             */
/*   Updated: 2025/01/15 15:22:21 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

int	is_builtin(t_executor *exec)
{
	if (!exec->exec_args.next)
		return (0);
	if (!exec->exec_args.next->arg)
		return (0);
	if (!ft_strcmp(exec->exec_args.next->arg, "cd") 
			|| !ft_strcmp(exec->exec_args.next->arg, "echo")
			|| !ft_strcmp(exec->exec_args.next->arg, "env")
			|| !ft_strcmp(exec->exec_args.next->arg, "export")
			|| !ft_strcmp(exec->exec_args.next->arg, "unset")
			|| !ft_strcmp(exec->exec_args.next->arg, "pwd")
			|| !ft_strcmp(exec->exec_args.next->arg, "exit"))
		return (1);
	return (0);
}

int	ft_arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	route_builtin(t_executor *exec, char **argv)
{
	char	*arg;

	arg = exec->exec_args.next->arg;
	//printf("routing builtin: '%s' param: '%s'\n", arg, argv[1]);fflush(stdout);
	if (!ft_strcmp(arg, "cd")) // THERE IS MORE TO IT IN THE MAIN(), CHECK OUT
		return (ft_cd(exec->env_variables, ft_arr_len(argv), argv));
	else if (!ft_strcmp(arg, "echo"))
		return (ft_echo(ft_arr_len(argv), argv));
	else if (!ft_strcmp(arg, "env"))	
		return (ft_env(exec->env_variables));
	else if (!ft_strcmp(arg, "export"))
		return (ft_export(exec->env_variables, ft_arr_len(argv), argv));
	else if (!ft_strcmp(arg, "pwd"))
		return (ft_pwd(exec->env_variables));
	else if (!ft_strcmp(arg, "unset"))
		return (ft_unset(exec->env_variables, ft_arr_len(argv), argv));
	else if (!ft_strcmp(arg, "exit")) // check this out
		return (2); //??
	return (0);
}

int	builtin_routine(t_executor *exec)
{
	char	**argv;
	char	*arg;
	int	ret;

	arg = exec->exec_args.next->arg;
	argv = list_to_arr_dup(exec->exec_args.next);
	if (!argv)
		return (1);
	if ((!ft_strcmp(arg, "cd") || !ft_strcmp(arg, "export") || !ft_strcmp(arg, "unset")
		|| !ft_strcmp(arg, "exit")) && (exec->prev || exec->next))
		return (free_nt_arr(argv), 0);
	ret = route_builtin(exec, argv);
	free_nt_arr(argv);
	return (ret);
}

