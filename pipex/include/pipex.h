/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:40:27 by vcaratti          #+#    #+#             */
/*   Updated: 2024/11/04 12:56:42 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_cmd
{
	char	*path;
	char	**args;
}	t_cmd;

typedef struct s_child_cmd
{
	int		child;
	t_cmd	cmd;
	int		*fd;
	int		*files;
	char	**envp;
}	t_child_cmd;

typedef struct s_pipex
{
	int		*pipes;
	int		files[2];
	int		*children;
	char	**argv;
	int		argc;
	char	**envp;
}	t_pipex;

// pipex.c //
int		get_nb_cmds(char **argv, int argc);

// cmd_path.c //
int		cmd_path(char *cmd, char **envp, char **ret);

// init_cmds.c //
int		init_cmds(t_cmd *in, t_cmd *out);

// tools.c //
int		free_cmds_e_ret(t_cmd *in, t_cmd *out, int error);
int		free_map_e_ret(char **arr, int error);
void	close_wait(t_pipex *data);
int		start_fork(int *childfd);
int		open_files(char *infile, char *outfile, int *file_fds, int i);

// children.c //
int		child_routine(t_cmd cmd, t_pipex *data, int n);
int		open_pipes_children(int nb_pipes, t_pipex *data);

#endif
