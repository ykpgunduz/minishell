/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::  */
/*   path_utils.c                                       :+:      :+:    :+  */
/*                                                      +:+ +:+         +:+   */
/*   By: zkarali <zkarali@student.42istanbul.com.tr>  +#+  +:+       +#+      */
/*                                                  +#+#+#+#+#+   +#+         */
/*   Created: 2026/03/28 13:04:06 by zkarali             #+#    #+#           */
/*   Updated: 2026/04/12 21:39:01 by zkarali            ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	for_check_stat(char *path, t_ms *data)
{
	struct stat	path_info;

	if (stat(path, &path_info) == 0)
	{
		if (S_ISDIR(path_info.st_mode))
		{
			for_err(path, NULL, "Is a directory");
			for_free(data);
			exit(126);
		}
	}
}

static char	*is_in_dir(char **com, t_ms *data)
{
	char	*path;
	char	*c;
	char	*s;

	path = for_env_value(*(data->envp), "PATH");
	if (!path)
	{
		c = getcwd(NULL, 0);
		s = making_str(c, *com);
		free(c);
		if (access(s, X_OK) == 0)
			return (s);
		free(s);
		return (NULL);
	}
	return (NULL);
}

char	*fir_check(char **com, t_ms *data)
{
	char	*true;

	if (!com || !com[0])
		return (NULL);
	true = is_in_dir(com, data);
	if (true)
		return (true);
	if (com[0][0] == '/' || (com[0][0] == '.' && com[0][1] == '/'))
	{
		if (access(com[0], F_OK) == -1)
		{
			for_err(com[0], NULL, strerror(errno));
			data->exit_num = 127;
			for_free(data);
			exit(127);
		}
		for_check_stat(com[0], data);
		if (access(com[0], X_OK) == -1)
		{
			for_err(com[0], NULL, strerror(errno));
			data->exit_num = 126;
			for_free(data);
			exit(126);
		}
		return (com[0]);
	}
	return (NULL);
}
