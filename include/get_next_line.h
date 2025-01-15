/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:36:07 by vcaratti          #+#    #+#             */
/*   Updated: 2025/01/15 14:45:01 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 200
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "../libft/include/libft.h"

int		has_endl(char *str, int is_not_buffer);
char	*get_first_line(char *buffer);
int		ft_arrlen(char *arr);
void	buffer_shift(char *buffer, int shift);
char	*array_to_mem(char *mem, char *buffer);
char	*empty_mem_rem(char **mem, char *rem, int error);
char	*mem_to_array_ret_firstl(char *mem, char *buffer);
char	*wipe_buffer(char *buffer);
char	*get_next_line(int fd);

#endif
