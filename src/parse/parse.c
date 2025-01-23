/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 04:04:01 by akostian          #+#    #+#             */
/*   Updated: 2025/01/23 11:05:24 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Fills return array with splited string
static int	fill_argv(char ***argv, const size_t argc, char *str)
{
	size_t	ret_index;
	size_t	skip;

	ret_index = 0;
	while (ret_index < argc)
	{
		while (*str && ft_isspace(*str))
			str++;
		skip = get_next_arg_len(str);
		(*argv)[ret_index++] = ft_substr(str, 0, skip);
		if (!(*argv)[(ret_index - 1)])
			return (free_arr_str(*argv), -1);
		str += skip;
	}
	(*argv)[ret_index] = 0;
	return (0);
}

// Returns a length of value of every var combined in argument
static ssize_t	calc_vars_size(char *arg, t_hashmap *env_variables)
{
	size_t	ret;
	char	*var;

	ret = 0;
	while (*arg)
	{
		if (*arg == '$')
		{
			if (*(arg + 1) && (*(arg + 1) == '?'))
			{
				ret += exit_code_length();
				arg++;
				continue ;
			}
			var = ft_substr(arg, 1, get_var_length(arg));
			if (!var)
				return (-1);
			ret += ft_strlen(env_variables->get(env_variables, var));
			free(var);
		}
		arg++;
	}
	return (ret);
}

// Inserts env variables, removes quotes from every argument
int	post_process_argv(
					char ***argv,
					const size_t argc,
					t_hashmap *env_variables
)
{
	ssize_t	vars_size;
	size_t	arg_n;
	char	*old_arg;

	arg_n = 0;
	while (arg_n < argc)
	{
		old_arg = (*argv)[arg_n];
		vars_size = calc_vars_size(old_arg, env_variables);
		if (vars_size == -1)
			return (free_arr_str(*argv), -1);
		(*argv)[arg_n] = process_arg(
				old_arg,
				vars_size + ft_strlen(old_arg) + 1,
				env_variables
				);
		free(old_arg);
		if (!(*argv)[arg_n])
			return (free_arr_n((void **)*argv, argc), -1);
		arg_n++;
	}
	return (0);
}

int	add_after_pipe(char **str, t_hashmap *env_variables)
{
	extern int		g_exit_code;
	char			*ret_str;

	ret_str = pipe_readline(env_variables);
	append_str(str, ret_str);
	free(ret_str);
	if (g_exit_code == 1)
		return (ENOMEM);
	else if (g_exit_code)
	{
		free(*str);
		*str = malloc(sizeof(char));
		if (!(*str))
			return (ENOMEM);
		(*str)[0] = '\0';
		if (g_exit_code == 3)
			g_exit_code = 0;
		return (0);
	}
	return (0);
}

char	**args_parse(char **str, t_hashmap *env_variables)
{
	ssize_t		argc;
	char		**ret;
	extern int	g_exit_code;

	if (**str && ends_with_pipe(*str))
		if (add_after_pipe(str, env_variables))
			return (NULL);
	if (check_quotes(*str))
	{
		(*str)[0] = 0;
		g_exit_code = 1;
		ft_printf("minishell: bad combination of quotes\n");
	}
	argc = calculate_argc(*str);
	if (argc == -1)
		return (NULL);
	ret = ft_calloc(argc + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	if (fill_argv(&ret, argc, *str) == -1)
		return (NULL);
	if (post_process_argv(&ret, argc, env_variables) == -1)
		return (NULL);
	return (ret);
}
