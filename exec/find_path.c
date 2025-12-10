/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:23:10 by banne             #+#    #+#             */
/*   Updated: 2025/12/09 16:47:19 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**parse_envp(char **envp)
{
	int		i;
	char	**path;

	path = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
	return (path);
}

char	*get_full_path(char *dir, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	if (!full_path)
		return (NULL);
	return (full_path);
}

char	*check_path(int n, char **paths, char *cmd)
{
	int		i;
	char	*full_path;

	i = 0;
	while (i < n)
	{
		full_path = get_full_path(paths[i], cmd);
		if (!full_path)
		{
			free_tab(paths, n - 1);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			free_tab(paths, n - 1);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_tab(paths, n);
	return (NULL);
}

bool	exists_n_executable(char *path)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
			return (true);
		else
		{
			fprintf(stderr, "minishell: %s: Permission denied\n", path);
			return (false);
		}
	}
	fprintf(stderr, "minishell: %s: No such file or directory\n", path);
	return (false);
}

char	*find_cmd(t_cmd *cmd, char **envp)
{
	char	**paths;
	char	*full_path;
	int		n;

	if (!cmd || ft_strlen(cmd->args[0]) == 0)
		return (NULL);
	if (ft_strchr(cmd->args[0], '/'))
	{
		if (exists_n_executable(cmd->args[0]))
			return (ft_strdup(cmd->args[0]));
		else
			return (NULL);
	}
	paths = parse_envp(envp);
	if (!paths)
		return (NULL);
	n = 0;
	while (paths[n])
		n++;
	full_path = check_path(n, paths, cmd->args[0]);
	if (full_path)
		return (full_path);
	fprintf(stderr, "minishell: %s: command not found\n", cmd->args[0]);
	return (NULL);
}
