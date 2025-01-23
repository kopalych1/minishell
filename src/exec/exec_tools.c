/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:49:56 by vcaratti          #+#    #+#             */
/*   Updated: 2025/01/23 11:32:27 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

int	has_special_c(char *str)
{
	if (str[0] == '<' || str[0] == '>')
		return (1);
	return (0);
}

char	*trim_redirect(char *str)
{
	char	*ret;

	if (has_special_c(str + 1))
		return (NULL);
	if (str[0] != '<' && str[0] != '>')
		return (NULL);
	ret = ft_strdup(str + 1);
	return (ret);
}

int	get_nb_exec(t_executor *exec_head)
{
	int	i;

	i = 0;
	while (exec_head)
	{
		exec_head = exec_head->next;
		i++;
	}
	return (i);
}

void	ignore_signal(int signum)
{
	(void)signum;
}

int	check_exit(t_executor *exec_head, int *exec_ret)
{
	if (is_builtin(exec_head) && !exec_head->next)
	{
		if (!ft_strcmp(exec_head->exec_args.next->arg, "exit"))
		{
			if (!exec_head->exec_args.next->next)
				*exec_ret = 0;
			else
				*exec_ret = ft_atoi(exec_head->exec_args.next->next->arg);
			return (1);
		}
	}
	return (0);
}
