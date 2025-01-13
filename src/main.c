/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:59:05 by akostian          #+#    #+#             */
/*   Updated: 2025/01/09 13:25:31 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/exec.h"
#include "../include/hashmap.h"

unsigned char	g_exit_code = 0;

int	fill_env_variables(t_hashmap *env_variables)
{
	if (env_variables->set(env_variables, "PATH", getenv("PATH"), 0) == -1)
		return (ENOMEM);
	if (env_variables->set(env_variables, "USER", getenv("USER"), 0) == -1)
		return (ENOMEM);
	if (env_variables->set(env_variables, "HOME", getenv("HOME"), 0) == -1)
		return (ENOMEM);
	if (env_variables->set(env_variables, "PWD", getenv("PWD"), 0) == -1)
		return (ENOMEM);
	if (env_variables->set(env_variables, "OLDPWD", getenv("OLDPWD"), 0) == -1)
		return (ENOMEM);
	if (env_variables->set(env_variables, "NAME", getenv("NAME"), 0) == -1)
		return (ENOMEM);
	return (0);
}

void	append_str(char **str1, char *str2)
{
	char	*old_str;

	old_str = *str1;
	*str1 = ft_strjoin(*str1, str2);
	free(old_str);
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

#define NON_PRINT_START "\001"
#define NON_PRINT_END "\002"

char	*generate_promt(t_hashmap *env_variables)
{
	char	*promt;

	promt = NULL;
	append_str(&promt, NON_PRINT_START BHGRN NON_PRINT_END);
	append_str(&promt, env_variables->get(env_variables, "USER"));
	append_str(&promt, NON_PRINT_START CRESET NON_PRINT_END);
	append_str(&promt, NON_PRINT_START BHMAG NON_PRINT_END);
	append_str(&promt, "@");
	append_str(&promt, env_variables->get(env_variables, "NAME"));
	append_str(&promt, NON_PRINT_START CRESET NON_PRINT_END);
	append_str(&promt, ":");
	append_str(&promt, NON_PRINT_START BHBLU NON_PRINT_END);
	append_str(&promt, env_variables->get(env_variables, "PWD"));
	append_str(&promt, NON_PRINT_START CRESET NON_PRINT_END);
	append_str(&promt, "$ ");
	return (promt);
}

static int	route(
	int user_argc,
	char **user_argv,
	t_hashmap *env_variables,
	char **envp
)
{/*
	if (!ft_strcmp(user_argv[0], "exit"))
		return (1);
	if (!ft_strcmp(user_argv[0], "cd"))
	{
		g_exit_code = ft_cd(env_variables, user_argc, user_argv);
		if (g_exit_code == 1)
			printf("ft_cd: no such file or directory %s\n", user_argv[1]);
		else if (g_exit_code == ENOMEM)
			return (printf("ft_cd: not enough memory\n"), ENOMEM);
	}
	if (!ft_strcmp(user_argv[0], "echo"))
		g_exit_code = ft_echo(user_argc, user_argv);
	if (!ft_strcmp(user_argv[0], "pwd"))
		g_exit_code = ft_pwd(env_variables);
	if (!ft_strcmp(user_argv[0], "env"))
		g_exit_code = ft_env(env_variables);
	if (!ft_strcmp(user_argv[0], "unset"))
		g_exit_code = ft_unset(env_variables, user_argc, user_argv);
	if (!ft_strcmp(user_argv[0], "export"))
		g_exit_code = ft_export(env_variables, user_argc, user_argv);
	printf("%d\n", g_exit_code);*/
	(void)user_argc;
	int	exec_ret;
	exec_ret = 0;
	if (executor(user_argv, envp, env_variables, &exec_ret) == 1) // i have to handle this better, fix ret path of builtins
		return (1);
	return (0);
}

static int	minishell_noninteractive(
				char *arg,
				t_hashmap *env_variables,
				char **envp
)
{
	int		user_argc;
	char	**user_argv;

	user_argc = calculate_argc(arg);
	user_argv = args_parse(arg, env_variables);
	route(user_argc, user_argv, env_variables, envp);
	env_variables->free(env_variables);
	free_arr_str(user_argv);
	exit(0);
}

static int	minishell_interactive(
				t_hashmap *env_variables,
				char **envp
)
{
	char	*line;
	char	*promt;
	int		user_argc;
	char	**user_argv;

	using_history();
	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		promt = generate_promt(env_variables);
		if (!promt)
			return (ENOMEM);
		line = readline(promt);
		free(promt);

		user_argv = NULL;
		if (!line)
			break ;
		user_argc = calculate_argc(line);
		user_argv = args_parse(line, env_variables);
		if (!user_argv)
			return (free(line), rl_clear_history(), env_variables->free(env_variables), free_arr_str(user_argv), ENOMEM);

		if (user_argv[0])
			if (route(user_argc, user_argv, env_variables, envp))
				break ;

		add_history (line);
		free_arr_str(user_argv);
		free(line);
	}
	free(line);
	free_arr_str(user_argv);
	env_variables->free(env_variables);
	rl_clear_history();
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_hashmap	env_variables;

	if ((argc < 1) || (argc > 3))
		return (0);
	hm_init(&env_variables);
	if (fill_env_variables(&env_variables))
		return (ENOMEM);
	if (argc == 3)
		minishell_noninteractive(argv[2], &env_variables, envp);
	minishell_interactive(&env_variables, envp);
	return (0);
}

/*

Code to insert every env varialbe passed into main() inside env_variables

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
			return (-1);
		if (env_variables->set(env_variables, key, value, 0) == -1)
			return (-1);
		free(key);
		i++;
	}
	return (0);
} */
