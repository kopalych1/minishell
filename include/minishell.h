/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:56:41 by akostian          #+#    #+#             */
/*   Updated: 2024/10/23 16:59:03 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <dirent.h>

# include "../libft/include/libft.h"
# include "hashmap.h"

void	free_arr_str(char **arr);
void	free_arr_n(void **arr, size_t n);

/* PARSER */

/* parser utils */
size_t	get_var_length(char *str);
/*  */

char	**args_parse(char *str, t_hashmap *env_variables);
ssize_t	calculate_argc(char *str);
char	*process_arg(char *old_arg, size_t size, t_hashmap *env_variables);

/*  */

#endif