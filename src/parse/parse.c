/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 04:04:01 by akostian          #+#    #+#             */
/*   Updated: 2024/10/23 16:58:07 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static size_t	get_next_arg_len(char *str)
{
	char	quote_to_find;
	size_t	length;

	length = 0;
	while (*str && !ft_isspace(*str))
	{
		if (*str == '\'' || *str == '\"')
		{
			quote_to_find = *str++;
			length++;
			while (*str && *str != quote_to_find)
			{
				str++;
				length++;
			}
		}
		length++;
		str++;
	}
	return (length);
}

// Fills return array with splited string
static int	fill_argv(char ***argv, const size_t argc, char *str)
{
	size_t	ret_index;
	char	quote_to_find;

	ret_index = 0;
	while (ret_index < argc)
	{
		while (*str && ft_isspace(*str))
			str++;
		(*argv)[ret_index++] = ft_substr(str, 0, get_next_arg_len(str));
		if (!(*argv)[(ret_index - 1)])
			return (free_arr_str(*argv), -1);
		quote_to_find = 0;
		while (*str && !ft_isspace(*str))
		{
			if (*str == '\'' || *str == '\"')
			{
				quote_to_find = *str++;
				while (*str && *str != quote_to_find)
					str++;
			}
			str++;
		}
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
static int	post_process_argv(
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

char	**args_parse(char *str, t_hashmap *env_variables)
{
	const ssize_t	argc = calculate_argc(str);
	char			**ret;

	if (argc == -1)
		return (NULL);
	ret = ft_calloc(argc + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	if (fill_argv(&ret, argc, str) == -1)
		return (NULL);
	if (post_process_argv(&ret, argc, env_variables) == -1)
		return (NULL);
	return (ret);
}
