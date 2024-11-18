/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:32:29 by akostian          #+#    #+#             */
/*   Updated: 2024/11/18 17:04:38 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	verify_vars(t_hashmap *env_variables)
{
	if (!env_variables->get(env_variables, "PWD"))
		return (ENOMEM);
	if (!env_variables->get(env_variables, "OLDPWD"))
		return (ENOMEM);
	return (0);
}

int	ft_cd(t_hashmap *env_variables, int argc, char **argv)
{
	char	pwd[PATH_MAX];

	if (argc == 1)
	{
		if (!(env_variables->get(env_variables, "HOME")))
			return (0);
		chdir(env_variables->get(env_variables, "HOME"));
		env_variables->set(env_variables, "OLDPWD",
			ft_strdup(env_variables->get(env_variables, "PWD")), 1);
	}
	else if (argv[1][0] == '-' && !argv[1][1])
	{
		chdir(env_variables->get(env_variables, "OLDPWD"));
		env_variables->set(env_variables, "OLDPWD",
			ft_strdup(env_variables->get(env_variables, "PWD")), 1);
	}
	else if (chdir(argv[1]) == -1)
		return (1);
	getcwd(pwd, PATH_MAX);
	if (argc != 1 && !(argv[1][0] == '-' && !argv[1][1]))
		env_variables->set(env_variables, "OLDPWD",
			ft_strdup(env_variables->get(env_variables, "PWD")), 1);
	env_variables->set(env_variables, "PWD", ft_strdup(pwd), 1);
	return (verify_vars(env_variables));
}
