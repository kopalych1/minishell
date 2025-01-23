/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:59:05 by akostian          #+#    #+#             */
/*   Updated: 2025/01/23 12:11:39 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/exec.h"
#include "../include/hashmap.h"

int	g_exit_code;

int	fill_env_variables(t_hashmap *env_variables, char **envp)
{
	size_t	i;
	size_t	j;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		key = ft_substr(envp[i], 0, j);
		value = envp[i] + j + 1;
		if (!key || !value)
			return (env_variables->free(env_variables), -1);
		if (env_variables->set(env_variables, key, value, 0) == -1)
			return (free(key), env_variables->free(env_variables), -1);
		free(key);
		i++;
	}
	return (0);
}

static int	route(
	int user_argc,
	char **user_argv,
	t_hashmap *env_variables,
	int *minishell_ret
)
{
	extern int	g_exit_code;
	int			exec_ret;
	int			exec_err;

	(void)user_argc;
	exec_ret = 0;
	if (user_argv[0][0] == '\0')
		return (0);
	exec_err = executor(user_argv, env_variables, &exec_ret) == 1;
	if (exec_err)
		*minishell_ret = exec_ret;
	if (exec_ret == 2)
		g_exit_code = 130;
	else
		g_exit_code = exec_ret / 256;
	return (exec_err);
}

static int	minishell_noninteractive(
				char *arg,
				t_hashmap *env_variables,
				int *minishell_ret
)
{
	int		user_argc;
	char	**user_argv;

	user_argc = calculate_argc(arg);
	user_argv = args_parse(&arg, env_variables);
	route(user_argc, user_argv, env_variables, minishell_ret);
	env_variables->free(env_variables);
	free_arr_str(user_argv);
	exit(0);
}

static int	minishell_interactive(
				t_hashmap *env_variables,
				int *minishell_ret
)
{
	char	*line;
	int		user_argc;
	char	**user_argv;

	using_history();
	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		line = get_user_input(env_variables);
		user_argv = NULL;
		if (!line)
			break ;
		user_argc = calculate_argc(line);
		user_argv = args_parse(&line, env_variables);
		if (!user_argv)
			return (free_stuff(&line, env_variables, &user_argv), ENOMEM);
		if (user_argv[0])
			if (route(user_argc, user_argv, env_variables, minishell_ret))
				break ;
		add_history (line);
		free_arr_str(user_argv);
		free(line);
	}
	return (free_stuff(&line, env_variables, &user_argv), 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_hashmap	env_variables;
	int			minishell_ret;

	minishell_ret = 0;
	if ((argc < 1) || (argc > 3))
		return (0);
	hm_init(&env_variables);
	if (fill_env_variables(&env_variables, envp))
		return (ENOMEM);
	if (argc == 3)
	{
		if (ft_strcmp(argv[1], "-c"))
			return (0);
		minishell_noninteractive(argv[2], &env_variables, &minishell_ret);
	}
	else
		minishell_interactive(&env_variables, &minishell_ret);
	return (minishell_ret);
}
