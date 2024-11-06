/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:56:41 by akostian          #+#    #+#             */
/*   Updated: 2024/10/31 19:07:07 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <limits.h>

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

/* BUILT-IN */

int		ft_cd(t_hashmap *env_variables, int argc, char **argv);
int		ft_echo(int argc, char **argv);
int		ft_pwd(t_hashmap *env_variables);
int		ft_env(t_hashmap *env_variables);
int		ft_unset(t_hashmap *env_variables, int argc, char **argv);

/*  */

#endif
