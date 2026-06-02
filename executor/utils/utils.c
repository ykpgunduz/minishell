/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 20:21:34 by zkarali           #+#    #+#             */
/*   Updated: 2026/06/02 14:47:13 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char	**for_sh(char *path, t_cmd *cmd)
{
	int		ac;
	char	**sh;
	int		i;

	ac = 0;
	while (cmd->args[ac])
		ac++;
	sh = malloc(sizeof(char *) * (ac + 2));
	if (!sh)
		return (NULL);
	sh[0] = "sh";
	sh[1] = path;
	i = 0;
	while (cmd->args[i])
	{
		sh[i + 2] = cmd->args[i];
		i++;
	}
	sh[i + 1] = NULL;
	return (sh);
}

void	for_enoexec(t_cmd *cmd, char *path, char **env, t_ms *data)
{
	char	**sh;

	sh = for_sh(path, cmd);
	execve("/bin/sh", sh, env);
	for_err(cmd->args[0], NULL, strerror(errno));
	free(sh);
	free(path);
	free_s(env);
	data->exit_num = 126;
	for_free(data);
	exit(126);
}

void	before_path(t_cmd *cmd, t_ms *data)
{
	int	i;

	if (!cmd->args || !cmd->args[0])
	{
		i = data->exit_num;
		for_free(data);
		exit(i);
	}
	if (is_builtin(cmd))
	{
		for_builtin(cmd, data);
		i = data->exit_num;
		for_free(data);
		exit(i);
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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
