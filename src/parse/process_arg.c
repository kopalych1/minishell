/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 08:48:55 by akostian          #+#    #+#             */
/*   Updated: 2025/01/18 12:10:27 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static ssize_t	write_var(
			char **ret,
			size_t *i,
			char *old_arg,
			t_hashmap *env_variables
)
{
	char	*var;
	char	*var_value;
	size_t	var_lenght;
	size_t	j;

	var_lenght = get_var_length(old_arg);
	var = ft_substr(old_arg, 1, var_lenght);
	if (!var)
		return (-1);
	var_value = env_variables->get(env_variables, var);
	if (var_value)
	{
		j = *i;
		while (*var_value)
			(*ret)[j++] = *var_value++;
		*i = j;
	}
	free(var);
	return (get_var_length(old_arg) + 1);
}

static void	treat_single_q(char **old_arg, char **ret, size_t *i)
{
	(*old_arg)++;
	while (*(*old_arg) && *(*old_arg) != '\'')
		(*ret)[(*i)++] = *(*old_arg)++;
	(*old_arg)++;
}

static int	treat_var(
			char **ret,
			size_t *i,
			char **old_arg,
			t_hashmap *env_variables
)
{
	ssize_t		written_length;
	extern int	g_exit_code;
	char		*exit_code_str;
	int			j;

	if (ft_strchr("\'\"", *(*old_arg + 1)))
		return ((*ret)[(*i)++] = '$', *old_arg = *old_arg + 1, 0);
	if (*(*old_arg + 1) && *(*old_arg + 1) == '?')
	{
		exit_code_str = ft_itoa(g_exit_code);
		j = 0;
		while (exit_code_str[j])
			(*ret)[(*i)++] = exit_code_str[j++];
		return (*old_arg = *old_arg + j, free(exit_code_str), 0);
	}
	written_length = write_var(ret, i, *old_arg, env_variables);
	if (written_length == -1)
		return (-1);
	*old_arg = *old_arg + written_length;
	return (0);
}

static int	treat_double_q(
			char **ret,
			size_t *i,
			char **old_arg,
			t_hashmap *env_variables
)
{
	ssize_t	written_length;

	(*old_arg)++;
	while (*(*old_arg) && *(*old_arg) != '\"')
	{
		if (*(*old_arg) == '$')
		{
			written_length = treat_var(ret, i, old_arg, env_variables);
			if (written_length == -1)
				return (-1);
		}
		else
			(*ret)[(*i)++] = *(*old_arg)++;
	}
	(*old_arg)++;
	return (0);
}

// Returns a processed argument with inserted vars, and removed quotes
char	*process_arg(char *old_arg, size_t size, t_hashmap *env_variables)
{
	ssize_t	written_length;
	char	*ret;
	size_t	i;

	ret = malloc(size * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (*old_arg)
	{
		written_length = 0;
		if (*old_arg == '\'')
			treat_single_q(&old_arg, &ret, &i);
		else if (*old_arg == '\"')
			written_length = treat_double_q(&ret, &i, &old_arg, env_variables);
		else if (*old_arg == '$')
			written_length = treat_var(&ret, &i, &old_arg, env_variables);
		else
			ret[i++] = *old_arg++;
		if (written_length == -1)
			return (free(ret), NULL);
	}
	ret[i] = 0;
	return (ret);
}
