/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:59:05 by akostian          #+#    #+#             */
/*   Updated: 2024/12/11 14:11:59 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/exec.h"
#include "../include/hashmap.h"

unsigned char	exit_code = 0;

void	print_splited(char **splited)
{
	size_t	i;

	i = 0;
	while (splited[i])
		printf(""BBLU"\""CRESET"%s"BBLU"\""CRESET"\n", splited[i++]);
}

int	fill_env_variables(t_hashmap *env_variables)
{
	env_variables->set(env_variables, "PATH", getenv("PATH"), 0);
	env_variables->set(env_variables, "USER", getenv("USER"), 0);
	env_variables->set(env_variables, "HOME", getenv("HOME"), 0);
	env_variables->set(env_variables, "PWD", getenv("PWD"), 0);
	env_variables->set(env_variables, "OLDPWD", getenv("OLDPWD"), 0);
	env_variables->set(env_variables, "NAME", getenv("NAME"), 0);
	return (0);
}

void	append_str(char **str1, char *str2)
{
	char	*old_str;

	old_str = *str1;
	*str1 = ft_strjoin(*str1, str2);
	free(old_str);
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

size_t	ft_max(size_t val1, size_t val2)
{
	if (val1 > val2)
		return (val1);
	return (val2);
}

void	print_args(char **args)
{
	int	i = 0;
	while (args[i])
		printf("[%s]", args[i++]);
	write(1, "\n", 1);
}

int	main(int argc, char **argv, char **envp)
{
	t_hashmap	env_variables;
	char		*line;
	char		*promt;
	int			user_argc;
	char		**user_argv;

	if (argc != 1)
	{
		printf(MAG"%d"CRESET":\n", argc);
		for (int i = 0; i < argc; i++)
			printf(YEL"%s\n"CRESET, argv[i]);
		exit(0);
	}
	hm_init(&env_variables);
	fill_env_variables(&env_variables);
	using_history();

	while (1)
	{
		promt = generate_promt(&env_variables);
		line = readline(promt);
		free(promt);

		user_argc = calculate_argc(line);
		user_argv = args_parse(line, &env_variables);
		if (!user_argv)
			return (free(line), clear_history(), env_variables.free(&env_variables), free_arr_str(user_argv), 1);

		//print_args(user_argv);
		 printf(BYEL"%d\n"CRESET, user_argc);
		 print_splited(user_argv);

		if (user_argv[0])
		{
			if (!ft_strcmp(user_argv[0], "exit"))
				break ;

			if (!ft_strcmp(user_argv[0], "cd"))
			{
				exit_code = ft_cd(&env_variables, user_argc, user_argv);
				if (exit_code == 1)
					printf("ft_cd: no such file or directory %s\n", user_argv[1]);
				else if (exit_code == 2)
				{
					printf("ft_cd: not enough memory\n");
					break ;
				}
			}
			if (!ft_strcmp(user_argv[0], "echo"))
				exit_code = ft_echo(user_argc, user_argv);
			if (!ft_strcmp(user_argv[0], "pwd"))
				exit_code = ft_pwd(&env_variables);
			if (!ft_strcmp(user_argv[0], "env"))
				exit_code = ft_env(&env_variables);
			executor(user_argv, envp); 
		}

		add_history (line);
		free_arr_str(user_argv);
		free(line);
	}
	free(line);
	free_arr_str(user_argv);
	env_variables.free(&env_variables);
	clear_history();

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
