/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:50:12 by vcaratti          #+#    #+#             */
/*   Updated: 2023/11/03 13:49:12 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	get_array_len(const char *str, char c)
{
	int	i;
	int	w_counter;
	int	w_len;

	i = 0;
	w_counter = 0;
	w_len = 0;
	while (str[i])
	{
		if (str[i] == c && w_len)
		{
			w_counter++;
			w_len = 0;
		}
		if (str[i] != c)
			w_len++;
		i++;
	}
	if (w_len)
		w_counter++;
	return (w_counter);
}

static int	fill_array(char const *s, char c, char **array, int array_l)
{
	int		i;
	int		j;
	int		x;
	char	*n_word;

	i = 0;
	x = 0;
	while (i < array_l)
	{
		while (s[x] == c)
			x++;
		j = 0;
		while (s[x + j] != c && s[x + j] != '\0')
			j++;
		n_word = ft_substr(s, x, j);
		if (n_word == NULL)
			return (i);
		array[i] = n_word;
		while (s[x] != '\0' && s[x] != c)
			x++;
		i++;
	}
	return (-1);
}

static void	*free_all(char **arr, int max)
{
	int	i;

	i = 0;
	while (i <= max)
		free(arr[i++]);
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	int		array_l;
	int		ans;

	if (s == NULL)
		return (NULL);
	array_l = get_array_len(s, c);
	ret = malloc(sizeof(char *) * (array_l + 1));
	if (ret == NULL)
		return (NULL);
	ret[array_l] = 0;
	ans = fill_array(s, c, ret, array_l);
	if (ans != -1)
		return (free_all(ret, ans - 1));
	return (ret);
}
