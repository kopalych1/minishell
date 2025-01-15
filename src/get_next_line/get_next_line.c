/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:46:08 by vcaratti          #+#    #+#             */
/*   Updated: 2025/01/15 14:47:05 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"

void	buffer_shift(char *buffer, int shift)
{
	int	i;

	i = 0;
	while (shift < BUFFER_SIZE)
	{
		buffer[i] = buffer[shift];
		buffer[shift] = 0;
		i++;
		shift++;
	}
}

char	*empty_mem_rem(char **mem, char *rem, int error)
{
	char	*temp;

	wipe_buffer(rem);
	if (error < 0)
	{
		free(*mem);
		return (NULL);
	}
	if (ft_strlen(*mem) == 0)
	{
		free(*mem);
		return (NULL);
	}
	temp = *mem;
	*mem = NULL;
	return (temp);
}

char	*mem_to_array_ret_firstl(char *mem, char *buffer)
{
	int		endl;
	char	*ret;
	int		counter;

	endl = has_endl(mem, 1);
	ret = malloc((endl + 1) * sizeof(char));
	if (!ret)
		return (free(mem), NULL);
	counter = -1;
	while (++counter < endl)
		ret[counter] = mem[counter];
	ret[counter] = '\0';
	counter = endl;
	while (mem[counter] && (counter - endl) < BUFFER_SIZE)
	{
		buffer[counter - endl] = mem[counter];
		counter++;
	}
	free(mem);
	return (ret);
}

char	*wipe_buffer(char *buffer)
{
	int	counter;

	counter = 0;
	while (counter < BUFFER_SIZE)
		buffer[counter++] = 0;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	rem[BUFFER_SIZE];
	char		buffer[BUFFER_SIZE];
	char		*mem;
	int			b_read;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 256)
		return (NULL);
	if (has_endl(rem, 0) >= 0)
		return (get_first_line(rem));
	mem = array_to_mem(NULL, rem);
	if (mem == NULL)
		return (wipe_buffer(rem));
	while (has_endl(mem, 1) < 0)
	{
		wipe_buffer(buffer);
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read <= 0)
			return (empty_mem_rem(&mem, rem, b_read));
		mem = array_to_mem(mem, buffer);
		if (mem == NULL)
			return (wipe_buffer(rem));
	}
	return (mem_to_array_ret_firstl(mem, rem));
}
