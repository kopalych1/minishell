/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:32:52 by akostian          #+#    #+#             */
/*   Updated: 2024/10/23 16:57:58 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_arr_str(char **arr)
{
	size_t	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			free(arr[i++]);
		free(arr[i]);
	}
	free(arr);
}

void	free_arr_n(void **arr, size_t n)
{
	if (arr)
	{
		free(arr[n]);
		while (n--)
			free(arr[n]);
	}
	free(arr);
}
