/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:43:18 by vcaratti          #+#    #+#             */
/*   Updated: 2025/01/21 12:13:13 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"

int	has_endl(char *str, int is_not_buffer)
{
	int	counter;

	if (!str)
		return (-1);
	counter = 0;
	while (str[counter] && (is_not_buffer == 1 || counter < BUFFER_SIZE))
	{
		if (str[counter] == '\n')
			return (counter + 1);
		counter++;
	}
	return (-1);
}

char	*get_first_line(char *buffer)
{
	int		counter;
	int		i;
	char	*ret;

	counter = 0;
	while (counter < BUFFER_SIZE && buffer[counter] != '\n')
		counter++;
	counter++;
	if (counter == BUFFER_SIZE)
		return (0);
	ret = malloc((counter + 1) * sizeof(char));
	if (ret == NULL)
		return (0);
	i = -1;
	while (++i < counter)
		ret[i] = buffer[i];
	ret[i] = '\0';
	i = 0;
	buffer_shift(buffer, counter);
	return (ret);
}

int	ft_arrlen(char *arr)
{
	int	count;

	count = 0;
	while (count < BUFFER_SIZE && arr[count])
		count++;
	return (count);
}

char	*array_to_mem(char *mem, char *buffer)
{
	int		a_size;
	int		m_size;
	char	*ret;
	int		count;

	a_size = ft_arrlen(buffer);
	m_size = ft_strlen(mem);
	ret = malloc((a_size + m_size + 1) * sizeof(char));
	if (ret == NULL)
		return (free(mem), NULL);
	count = -1;
	while (mem && count++ < m_size)
		ret[count] = mem[count];
	count = -1;
	while (++count < a_size)
	{
		ret[m_size + count] = buffer[count];
		buffer[count] = 0;
	}
	ret[m_size + count] = '\0';
	if (mem)
		free(mem);
	return (ret);
}
