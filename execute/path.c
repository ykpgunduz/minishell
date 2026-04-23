/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:06:15 by zkarali           #+#    #+#             */
/*   Updated: 2026/04/07 12:58:47 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	check_stat(char *path, t_list *envp, char *line, t_list *cmds)
{
	struct stat	path_info;

	if (stat(path, &path_info) == 0)
	{
		if (S_ISDIR(path_info.st_mode))
		{
			write(2, "minishell: ", 11);
			write(2, path, ft_strlen(path));
			write(2, ": is a directory\n", 17);
			for_free(envp, line, cmds);
			exit(126);
		}
	}
}

static char	*making_str(char *paths, char *command)
{
	char	*str;
	char	*str2;

	str = ft_strjoin(paths, "/");
	if (!str)
		return (NULL);
	str2 = ft_strjoin(str, command);
	if (!str2)
		return (NULL);
	free(str);
	return (str2);
}

static int	for_access(char *true, t_list *envp, char *line, t_list *cmds)
{
	if (access(true, X_OK) == 0)
	{
		check_stat(true, envp, line, cmds);
		return (1);
	}
	return (0);
}

char	*check_path(char *command, t_list *envp, char *line, t_list *cmds)
{
	char	*path;
	char	**paths;
	char	*true;
	int		i;

	if (command[0] == '\0')
		return (NULL);
	path = for_env_value(envp, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		true = making_str(paths[i], command);
		if (!true)
			return (free_s(paths, 2), free(true), NULL);
		if (for_access(true, envp, line, cmds) == 1)
			return (free_s(paths, 2), true);
		free(true);
		i++;
	}
	return (free_s(paths, 2), NULL);
}

char	*fir_check(char **com, t_list *envp, char *line, t_list *cmds)
{
	int	i;

	if (com[0][0] == '/' || com[0][0] == '.')
	{
		i = access(com[0], X_OK);
		if (i == 0)
		{
			check_stat(com[0], envp, line, cmds);
			return (com[0]);
		}
		else if (i == -1)
		{
			perror("No such file or directory");
			for_free(envp, line, cmds); //free yeterli mi
			exit(127);
		}
	}
	return (NULL);
}
