/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:49:58 by akostian          #+#    #+#             */
/*   Updated: 2024/10/30 19:20:49 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_echo(int argc, char **argv)
{
	unsigned char	do_print_nl;
	int				i;

	do_print_nl = 1;
	if (argc > 1)
		do_print_nl = ft_strcmp(argv[1], "-n");
	i = 1;
	while (i < argc)
	{
		ft_printf(argv[i++]);
		if (i < argc)
			ft_printf(" ");
	}
	if (do_print_nl)
		ft_printf("\n");
	return (0);
}
