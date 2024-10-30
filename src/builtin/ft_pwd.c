/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:31:31 by akostian          #+#    #+#             */
/*   Updated: 2024/10/30 19:49:44 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// char *getcwd(char *buf, size_t size);
int	ft_pwd(t_hashmap *env_variables)
{
	ft_printf("%s\n", env_variables->get(env_variables, "PWD"));
	return (0);
}
