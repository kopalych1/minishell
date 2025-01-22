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

static int	check_cd_home(t_hashmap *env_variables)
{
	if (!(env_variables->get(env_variables, "HOME")))
		return (1);
	if (chdir(env_variables->get(env_variables, "HOME")) == -1)
		return (2);
	if (env_variables->set(env_variables, "OLDPWD",
			ft_strdup(env_variables->get(env_variables, "PWD")), 1) == -1)
		return (2);
	return (0);
}

static int	goto_oldpwd(t_hashmap *env_variables)
{
	if (chdir(env_variables->get(env_variables, "OLDPWD")) == -1)
		return (1);
	if (env_variables->set(env_variables, "OLDPWD",
			ft_strdup(env_variables->get(env_variables, "PWD")), 1) == -1)
		return (1);
	return (0);
}

static int	cd_continuation(int argc, char **argv,
			char *pwd, t_hashmap *env_variables)
{
	if (getcwd(pwd, PATH_MAX) == NULL)
		return (1);
	if (argc != 1 && !(argv[1][0] == '-' && !argv[1][1]))
	{
		if (env_variables->set(env_variables, "OLDPWD",
				ft_strdup(env_variables->get(env_variables, "PWD")), 1) == -1)
			return (1);
	}
	if (env_variables->set(env_variables, "PWD", ft_strdup(pwd), 1) == -1)
		return (1);
	return (0);
}

int	ft_cd(t_hashmap *env_variables, int argc, char **argv)
{
	char	pwd[PATH_MAX];
	int		ret;

	if (argc == 1)
	{
		ret = check_cd_home(env_variables);
		if (ret)
			return (ret - 1);
	}
	else if (argv[1][0] == '-' && !argv[1][1])
	{
		if (goto_oldpwd(env_variables))
			return (1);
	}
	else if (chdir(argv[1]) == -1)
		return (1);
	if (cd_continuation(argc, argv, pwd, env_variables))
		return (1);
	return (verify_vars(env_variables));
}
