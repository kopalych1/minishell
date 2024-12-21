/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:37:51 by vcaratti          #+#    #+#             */
/*   Updated: 2024/12/19 15:54:53 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../libft/include/libft.h"
# include "stdlib.h"
# include "stdio.h"
# include "sys/wait.h"
# include "sys/types.h"

typedef struct s_cmd
{
	char	*path;
	char	**args;
}	t_cmd;

typedef struct s_elist
{
	struct s_elist	*prev;
	struct s_elist	*next;
	char	*arg;
	char	mode;
}	t_elist;

typedef	struct s_executor
{
	struct s_executor	*prev;
	struct s_executor	*next;
	t_elist				infiles;
	t_elist				outfiles;
	t_elist				exec_args;
	t_cmd				cmd;
	char				**envp;
	int					fid;
	int					pipes[2];
	int					fds[2];
}	t_executor;

//#===#		executor.c		#===#//

int	exec_routine(t_executor *exec);
int	start_pipes(t_executor *exec_head);
int	executor(char **args, char **envp);

//#===#		exec_free.c		#===#//

int		free_and_ret(char **to_free, int ret);
void	free_all(t_executor *head);
void	free_nt_arr(char **arr);
void	free_list(t_elist *head);
void	free_list_node(t_elist *list);

//#===#		cmd_path.c		#===#//

int	treat_cmd(t_executor *exec);
int	path_index(char **envp);
char	*join_path_cmd(char *path, char *cmd);
int	find_path(char *cmd, char **paths, char **ret);
int	cmd_path(char *cmd, char **envp, char **ret);

//#===#		list_tools.c	#===#//

int	list_len(t_elist *head);
char	**list_to_arr(t_elist *head);
t_elist	*list_pop(t_elist *elem);
int	list_append_arg(t_elist *lst, char *arg);
void	list_append(t_elist *lst, t_elist *node);

//#===#		exec_init.c		#===#//

int	init_children_pipes(t_executor *exec_head);
int	init_cmd_args(t_executor *exec_head);
int	create_exec(t_executor **ret, t_executor *p, t_executor *n, char **envp);
int	fetch_redirect(t_elist *current, t_executor *current_exec);
int	list_init(t_elist *args_head, char **args);

//#===#		exec_tools.c	#===#//

int	has_special_c(char *str);
char	*trim_redirect(char *str);
int	get_nb_exec(t_executor *exec_head);

//#===#		exec_io.c		#===#//

int	open_outfiles(t_elist *outfiles);
int	open_infiles(t_elist *infiles);
void	close_all_except(t_executor *exec);

#endif
