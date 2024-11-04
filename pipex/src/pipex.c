/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:54:03 by vcaratti          #+#    #+#             */
/*   Updated: 2024/11/04 13:02:48 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	treat_cmd(char *cmd, char **envp, t_cmd *ret)
{
	int	path_return;

	ret->args = ft_split(cmd, ' ');
	if (ret->args == NULL || ret->args[0] == NULL)
		return (-1);
	path_return = cmd_path(ret->args[0], envp, &(ret->path));
	if (path_return == -1)
		return (-1);
	if (path_return == -2)
	{
		write(2, "Command not found\n", 18);
		return (-1);
	}
	return (0);
}

int	get_nb_cmds(char **argv, int argc)
{
	int	nb;

	nb = argc - 1;
	if (argv[1][0] == '<')
		nb -= 2;
	if (argv[argc - 2][0] == '>')
		nb -= 2;
	return (nb);
}

static int	open_redirections(t_pipex *data, int i)
{
	char	**argv;
	int		argc;

	argv = data->argv;
	argc = data->argc;
	if (argv[1][0] != '<')
	{
		if (argv[argc - 2][0] != '>')
			open_files(NULL, NULL, data->files, i);
		else if (open_files(NULL, argv[argc - 1], data->files, i) == -1)
			return (-1);
	}
	else if (argv[argc - 2][0] != '>')
	{
		if (open_files(argv[2], NULL, data->files, i) == -1)
			return (-1);
	}
	else
	{
		if (open_files(argv[2], argv[argc - 1], data->files, i) == -1)
			return (-1);
	}
	return (0);
}

static int	run2(t_pipex *data)
{
	t_cmd	cmd;
	int		n;
	int		i;

	n = 0;
	i = 1;
	if (data->argv[1][0] == '<')
		i = 3;
	while (n < get_nb_cmds(data->argv, data->argc))
	{
		if (treat_cmd(data->argv[i], data->envp, &cmd) == -1
			|| start_fork(&(data->children[n])) == -1)
			return (free_cmds_e_ret(&cmd, NULL, -1));
		if (data->children[n] == 0)
		{
			if (child_routine(cmd, data, n) == -1)
				return (free_cmds_e_ret(&cmd, NULL, -1));
		}
		free_cmds_e_ret(&cmd, NULL, 0);
		n++;
		i++;
	}
	close_wait(data);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		ret;
	t_pipex	data;
	int		write_append;

	if (argc < 2)
		return (write(2, "Wrong number of arguments\n", 26), -1);
	data.argc = argc;
	data.argv = argv;
	data.envp = envp;
	write_append = 0;
	if (argv[argc - 2][1] == '>')
		write_append = 1;
	if (open_redirections(&data, write_append) == -1)
		return (-1);
	if (open_pipes_children(get_nb_cmds(argv, argc) - 1, &data) == -1)
		return (-1);
	ret = run2(&data);
	free(data.pipes);
	free(data.children);
	system("leaks pipex");
	return (ret);
}
//system("leaks pipex");

// TO WORK: INPUT MUST 	BE: < INFILE "COMMAND 1" ... "COMMAND n" > OUTFILE
//			OR: "COMMAND 1" ... "COMMAND n" > OUTFILE
//			OR: < INFILE "COMMAND 1" ... "COMMAND n"
