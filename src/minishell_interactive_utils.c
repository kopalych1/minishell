/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_interactive_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:04:04 by akostian          #+#    #+#             */
/*   Updated: 2025/01/22 10:27:08 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#define NON_PRINT_START "\001"
#define NON_PRINT_END "\002"

void	append_str(char **str1, char *str2)
{
	char	*old_str;

	old_str = *str1;
	*str1 = ft_strjoin(*str1, str2);
	free(old_str);
}

static char	*generate_promt(t_hashmap *env_variables)
{
	char	*promt;

	promt = NULL;
	append_str(&promt, NON_PRINT_START BHGRN NON_PRINT_END);
	append_str(&promt, env_variables->get(env_variables, "USER"));
	append_str(&promt, NON_PRINT_START CRESET NON_PRINT_END);
	append_str(&promt, NON_PRINT_START BHMAG NON_PRINT_END);
	append_str(&promt, "@");
	append_str(&promt, env_variables->get(env_variables, "NAME"));
	append_str(&promt, NON_PRINT_START CRESET NON_PRINT_END);
	append_str(&promt, ":");
	append_str(&promt, NON_PRINT_START BHBLU NON_PRINT_END);
	append_str(&promt, env_variables->get(env_variables, "PWD"));
	append_str(&promt, NON_PRINT_START CRESET NON_PRINT_END);
	append_str(&promt, "$ ");
	return (promt);
}

char	*get_user_input(t_hashmap *env_variables)
{
	char	*promt;
	char	*line;

	promt = generate_promt(env_variables);
	if (!promt)
		return (NULL);
	line = readline(promt);
	return (free(promt), line);
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	free_stuff(
			char **line,
			t_hashmap *env_variables,
			char ***user_argv
)
{
	free(*line);
	free_arr_str(*user_argv);
	env_variables->free(env_variables);
	rl_clear_history();
}
