/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:15:55 by vcaratti          #+#    #+#             */
/*   Updated: 2025/01/20 13:40:41 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

void	pop_hd_operator(t_elist **to_del, t_elist **node)
{
	(*to_del) = (*node);
	(*node) = (*to_del)->next;
	free_list_node(list_pop(*to_del));
}

void	hd_handle_interupt(int signum)
{
	if (signum == SIGINT || signum == 130)
	{
		if (signum == SIGINT)
			exit(1);
		printf("minishell: warning: here-document delimited by end-of-file\n");
		exit(130);
	}
}
