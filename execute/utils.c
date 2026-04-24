/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::  */
/*   utils.c                                              :+:      :+:    :+  */
/*                                                      +:+ +:+         +:+   */
/*   By: zkarali <zkarali@student.42istanbul.com.tr>  +#+  +:+       +#+      */
/*                                                  +#+#+#+#+#+   +#+         */
/*   Created: 2026/03/27 20:21:34 by zkarali             #+#    #+#           */
/*   Updated: 2026/04/20 05:49:41 by zkarali            ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"
#include "mini.h"

void	free_s(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	for_enoexec(t_cmd *cmd, char *path, char **env, t_ms *data)
{
	int		ac;
	char	**sh;
	int		i;

	ac = 0;
	while (cmd->args[ac])
		ac++;
	sh = malloc(sizeof(char *) * (ac + 2));
	if (!sh)
		return ;
	sh[0] = "sh";
	sh[1] = path;
	i = 0;
	while (cmd->args[i])
	{
		sh[i + 1] = cmd->args[i];
		i++;
	}
	sh[i + 1] = NULL;
	execve("/bin/sh", sh, env);
	for_err(cmd->args[0], NULL, strerror(errno));
	free(sh);
	data->exit_num = 126;
	exit(126);
}

void	before_path(t_cmd *cmd, t_ms *data)
{
	if (!cmd->args || !cmd->args[0])
	{
		for_free(data);
		exit(0);
	}
	if (is_builtin(cmd))
	{
		builtin_execute(cmd, data);
		for_free(data);
		exit(0);
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (p1[i] && p2[i])
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		i++;
	}
	return (0);
}

void	for_err(char *com, char *msg, char *err)
{
	ft_putstr_fd("minishell: ", 2);
	if (com)
	{
		ft_putstr_fd(com, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(err, 2);
}
