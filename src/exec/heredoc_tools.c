/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:30:16 by vcaratti          #+#    #+#             */
/*   Updated: 2025/01/16 13:32:53 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

void	pop_hd_operator(t_elist **to_del, t_elist **node)
{
	(*to_del) = (*node);
	(*node) = (*to_del)->next;
	free_list_node(list_pop(*to_del));
}

void	handle_interupt(int signum)
{
	if (signum == SIGINT || signum == 130)
	{
		if (signum == SIGINT)
			exit(1);
		printf("minishell: warning: here-document delimited by end-of-file\n");
		exit(130); // return code, needs to be in global?
	}
}
