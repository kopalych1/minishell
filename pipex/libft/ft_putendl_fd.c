/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:52:36 by vcaratti          #+#    #+#             */
/*   Updated: 2023/11/08 15:26:56 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	counter;

	if (!s)
		return ;
	counter = 0;
	while (s[counter])
		write(fd, &s[counter++], 1);
	write(fd, "\n", 1);
}
