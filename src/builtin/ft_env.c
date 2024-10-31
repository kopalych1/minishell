/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 04:46:25 by akostian          #+#    #+#             */
/*   Updated: 2024/10/31 05:04:19 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(t_hashmap *env_variables)
{
	size_t	i;

	i = 0;
	while (i < env_variables->length)
	{
		ft_printf("%s=%s\n",
			env_variables->items[i].key,
			env_variables->items[i].content);
		i++;
	}
	return (0);
}
