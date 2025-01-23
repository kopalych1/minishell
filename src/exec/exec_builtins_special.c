/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins_special.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:14:59 by vcaratti          #+#    #+#             */
/*   Updated: 2025/01/23 11:41:40 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

int	is_special_builtin(t_executor *exec)
{
	if (!exec->exec_args.next)
		return (0);
	if (!exec->exec_args.next->arg)
		return (0);
	if (!ft_strcmp(exec->exec_args.next->arg, "cd")
		|| !ft_strcmp(exec->exec_args.next->arg, "export")
		|| !ft_strcmp(exec->exec_args.next->arg, "unset"))
		return (1);
	return (0);
}

int	handle_cd(t_executor *exec, char **argv)
{
	extern int	g_exit_code;

	g_exit_code = ft_cd(exec->env_variables, ft_arr_len(argv), argv);
	if (g_exit_code == 1)
		printf("ft_cd: no such file or directory %s\n", argv[1]);
	else if (g_exit_code == ENOMEM)
		return (printf("ft_cd: not enough memory\n"), ENOMEM);
	return (0);
}

int	look_for_builtin(t_executor *exec_head)
{
	char	**argv;
	int		ret;

	ret = -1;
	if (exec_head->next || !is_special_builtin(exec_head))
		return (0);
	argv = list_to_arr_dup(exec_head->exec_args.next);
	if (!argv)
		return (1);
	if (!ft_strcmp(exec_head->exec_args.next->arg, "cd"))
		ret = handle_cd(exec_head, argv);
	else if (!ft_strcmp(exec_head->exec_args.next->arg, "export"))
		ret = ft_export(exec_head->env_variables, ft_arr_len(argv), argv);
	else if (!ft_strcmp(exec_head->exec_args.next->arg, "unset"))
	{
		ret = 0;
		if (ft_unset(exec_head->env_variables, ft_arr_len(argv), argv))
			ft_printf("minishell: Environment variable doesn't exist\n");
	}
	else if (!ft_strcmp(exec_head->exec_args.next->arg, "exit"))
		ret = 1;
	free_nt_arr(argv);
	ret++;
	return (ret);
}
