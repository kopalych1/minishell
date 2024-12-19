/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:51:55 by vcaratti          #+#    #+#             */
/*   Updated: 2024/12/18 15:51:35 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

int	treat_cmd(t_executor *exec)
{
	int	path_return;
	t_cmd	*ret;
	
	ret = &(exec->cmd);
	ret->args = list_to_arr(exec->exec_args.next);
	if (ret->args == NULL || ret->args[0] == NULL)
		return (1);
	path_return = cmd_path(ret->args[0], exec->envp, &(ret->path));
	if (path_return == -1)
		return (2);
	if (path_return == -2)
	{
		write(2, "Command not found\n", 18);
		return (3);
	}
	return (0);
}

int	path_index(char **envp)
{
	int	i;

	i = 0;
	if (!envp || !envp[0])
		return (write(2, "env not set\n", 12), -1);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	write(2, "PATH not found\n", 15);
	return (-1);
}

char	*join_path_cmd(char *path, char *cmd)
{
	char	*temp;
	char	*sep;
	char	*ret;

	sep = malloc(sizeof(char) * 2);
	if (sep == NULL)
		return (NULL);
	sep[0] = '/';
	sep[1] = '\0';
	temp = ft_strjoin(path, sep);
	free(sep);
	if (temp == NULL)
		return (NULL);
	ret = ft_strjoin(temp, cmd);
	free(temp);
	if (ret == NULL)
		return (NULL);
	return (ret);
}

int	find_path(char *cmd, char **paths, char **ret)
{
	char	*test_path;
	int	i;

	i = 0;
	*ret = NULL;
	if (!cmd || !paths || !paths[0])
		return (-1);
	while (paths[i] != 0)
	{
		test_path = join_path_cmd(paths[i], cmd);
		if (test_path == NULL)
			return (-1);
		if (access(test_path, X_OK) == 0)
		{
			*ret = test_path;
			return (0);
		}
		free(test_path);
		i++;
	}
	return (-2);
}

int	cmd_path(char *cmd, char **envp, char **ret)
{
	int	path_i;
	char	**paths;
	char	*paths_cpy;
	int	find_ret;

	path_i = path_index(envp);
	if (path_i < 0)
		return (-1);
	paths = ft_split(envp[path_i], '=');
	if (paths == NULL)
		return (-1);
	free(paths[0]);
	paths_cpy = paths[1];
	free(paths);
	paths = ft_split(paths_cpy, ':');
	if (paths == NULL)
		return (free(paths_cpy), -1);
	find_ret = find_path(cmd, paths, ret);
	if (find_ret == -1)
		return (free(paths_cpy), free_and_ret(paths, -1));
	if (find_ret == -2)
		return (free(paths_cpy), free_and_ret(paths, -2));
	return (free(paths_cpy), free_and_ret(paths, 0));
}
