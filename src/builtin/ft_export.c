/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:43:26 by akostian          #+#    #+#             */
/*   Updated: 2024/11/12 15:54:39 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_hashmap	*hm_items_copy(t_hashmap *src)
{
	t_hashmap	*dst;

	dst = malloc(sizeof(t_hashmap));
	if (!dst)
		return (NULL);
	ft_memcpy(dst, src, sizeof(t_hashmap));
	dst->items = malloc(src->length * sizeof(t_hashmap_item));
	if (!dst->items)
		return (free(dst), NULL);
	ft_memcpy(dst->items, src->items, src->length * sizeof(t_hashmap_item));
	return (dst);
}

/* Prints environment variables in alphabetical order */
static int	print_env_alph(t_hashmap *env_variables)
{
	size_t		i;
	t_hashmap	*env_copy;

	env_copy = hm_items_copy(env_variables);
	if (!env_copy)
		return (1);
	hm_sort_keys(env_copy);
	i = 0;
	while (i < env_variables->length)
	{
		ft_printf("declare -x %s", env_copy->items[i].key);
		if (env_copy->items[i].content)
			ft_printf("=\"%s\"", (char *)env_copy->items[i].content);
		i++;
		ft_printf("\n");
	}
	free(env_copy->items);
	free(env_copy);
	return (0);
}

static int	verify_arg(char *arg)
{
	const size_t	arg_len = ft_strlen(arg);
	size_t			i;

	i = 0;
	while (i < arg_len)
	{
		if (arg[i] == '=')
			return (1);
		if (!ft_isalnum(arg[i]))
			return (0);
		i++;
	}
	return (2);
}

static int	route(t_hashmap *env_variables, char *arg, int ver_code)
{
	size_t	j;
	char	*key;
	char	*val;

	if (ver_code == 2)
	{
		if (!env_variables->get(env_variables, arg))
			if (env_variables->set(env_variables, arg, NULL, 0) == -1)
				return (2);
	}
	if (ver_code == 1)
	{
		j = 0;
		while (arg[j++] != '=')
			;
		key = ft_substr(arg, 0, j - 1);
		val = ft_substr(arg, j, ft_strlen(arg + j));
		if (!key || !val)
			return (free(key), free(val), 2);
		if (env_variables->set(env_variables, key, val, 1) == -1)
			return (free(key), free(val), 2);
		free(key);
	}
	return (0);
}

int	ft_export(t_hashmap *env_variables, int argc, char **argv)
{
	int		i;
	int		ret_code;
	int		ver_code;

	ret_code = 0;
	if (argc < 2)
		return (print_env_alph(env_variables));
	i = 0;
	while (++i < argc)
	{
		if (!argv[i][0])
		{
			ret_code = 1;
			continue ;
		}
		ver_code = verify_arg(argv[i]);
		if (!ver_code)
		{
			ret_code = 1;
			continue ;
		}
		ret_code = route(env_variables, argv[i], ver_code);
	}
	return (ret_code);
}
