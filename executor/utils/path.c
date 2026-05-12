/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::  */
/*   path.c                                               :+:      :+:    :+  */
/*                                                      +:+ +:+         +:+   */
/*   By: zkarali <zkarali@student.42istanbul.com.tr>  +#+  +:+       +#+      */
/*                                                  +#+#+#+#+#+   +#+         */
/*   Created: 2026/03/28 13:04:06 by zkarali             #+#    #+#           */
/*   Updated: 2026/04/12 21:39:01 by zkarali            ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char	*making_str(char *paths, char *command)
{
	char	*str;
	char	*str2;

	str = ft_strjoin(paths, "/");
	if (!str)
		return (NULL);
	str2 = ft_strjoin(str, command);
	free(str);
	if (!str2)
		return (NULL);
	return (str2);
}

static int	for_access(char *true_path)
{
	if (access(true_path, X_OK) == 0)
		return (1);
	return (0);
}

static char	*find_in_paths(char **paths, char *command)
{
	char		*true_path;
	int			i;
	struct stat	path;

	i = -1;
	while (paths[++i])
	{
		true_path = making_str(paths[i], command);
		if (!true_path)
			break ;
		if (for_access(true_path) == 1)
		{
			if (stat(true_path, &path) == 0 && S_ISDIR(path.st_mode))
			{
				free(true_path);
				continue ;
			}
			free_s(paths);
			return (true_path);
		}
		free(true_path);
	}
	free_s(paths);
	return (NULL);
}

char	*check_path(char *command, t_ms *data)
{
	char	*path;
	char	**paths;

	if (!command || !command[0])
		return (NULL);
	path = for_env_value(*(data->envp), "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	return (find_in_paths(paths, command));
}
