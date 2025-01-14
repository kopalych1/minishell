/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:51:55 by vcaratti          #+#    #+#             */
/*   Updated: 2025/01/14 12:12:49 by vcaratti         ###   ########.fr       */
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
	path_return = cmd_path(ret->args[0], exec->env_variables, &(ret->path));
	if (path_return == -1)
		return (2);
	if (path_return == -2)
	{
		exec->bad_command = 1;
	//	write(2, "Command not found\n", 18);
	}
	return (0);
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

int	cmd_path(char *cmd, t_hashmap *env_variables, char **ret)
{
	char	*env_path;
	char	**paths;
	int	find_ret;

	if (access(cmd, X_OK) == 0)
	{
		*ret = ft_strdup(cmd);
		return (0);
	}
	env_path = env_variables->get(env_variables, "PATH");
	if (!env_path)
		return (-1);
	paths = ft_split(env_path, ':');
	if (paths == NULL)
		return ( -1);
	find_ret = find_path(cmd, paths, ret);
	if (find_ret == -1)
		return (free_and_ret(paths, -1));
	if (find_ret == -2)
		return (free_and_ret(paths, -2));
	return (free_and_ret(paths, 0));
}
