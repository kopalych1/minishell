/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:43:57 by vcaratti          #+#    #+#             */
/*   Updated: 2024/07/15 15:14:09 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_cmds(t_cmd *in, t_cmd *out)
{
	in->args = NULL;
	in->path = NULL;
	out->args = NULL;
	out->path = NULL;
	return (1);
}
