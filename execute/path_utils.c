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

#include "builtin/builtin.h"
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

char	*fir_check(char **com, t_ms *data)
{
	if (!com || !com[0])
		return (NULL);
	if (com[0][0] == '/' || (com[0][0] == '.' && com[0][1] == '/'))
	{
		if (access(com[0], F_OK) == -1)
		{
			for_err(com[0], NULL, strerror(errno));
			data->exit_num = 127;
			for_free(data);
			exit(127);
		}
		if (access(com[0], X_OK) == -1)
		{
			for_err(com[0], NULL, strerror(errno));
			data->exit_num = 126;
			for_free(data);
			exit(126);
		}
		for_check_stat(com[0], data);
		return (com[0]);
	}
	return (NULL);
}
