/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::  */
/*   exec2.c                                              :+:      :+:    :+  */
/*                                                      +:+ +:+         +:+   */
/*   By: zkarali <zkarali@student.42istanbul.com.tr>  +#+  +:+       +#+      */
/*                                                  +#+#+#+#+#+   +#+         */
/*   Created: 2026/03/31 01:37:06 by zkarali             #+#    #+#           */
/*   Updated: 2026/04/11 03:48:04 by zkarali            ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	child_p(t_chi *chi, t_cmd *cmd, t_list *tmp, t_ms *data)
{
	int	write;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	for_read(cmd, chi->prev_fd, data);
	write = for_outfile(cmd);
	if (write == -1)
	{
		for_err(cmd->outfile, NULL, strerror(errno));
		for_free(data);
		exit(1);
	}
	else if (write > 1)
	{
		dup2(write, STDOUT_FILENO);
		close(write);
	}
	else if (tmp->next)
		dup2(chi->fd[1], STDOUT_FILENO);
	if (tmp->next)
	{
		close(chi->fd[1]);
		close(chi->fd[0]);
	}
}

static void	parent_p(t_chi *chi, t_list *tmp)
{
	if (chi->prev_fd != 0)
		close(chi->prev_fd);
	if (tmp->next)
	{
		chi->prev_fd = chi->fd[0];
		close(chi->fd[1]);
	}
	else
		chi->prev_fd = 0;
}

static int	for_pipe(int *fd, t_list *tmp)
{
	if (tmp->next)
	{
		if (pipe(fd) == -1)
			return (perror("pipe"), 1);
	}
	return (0);
}

static int	for_fork(pid_t pid, t_chi *chi, t_list *tmp)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pid < 0)
	{
		for_err("fork", NULL, strerror(errno));
		return (1);
	}
	if (pid > 0)
		parent_p(chi, tmp);
	return (0);
}

pid_t	pipe_loop(t_ms *data, t_list *tmp)
{
	t_chi	chi;
	pid_t	pid;
	t_cmd	*cmd;

	chi.prev_fd = 0;
	while (tmp)
	{
		cmd = (t_cmd *)tmp->content;
		if (for_pipe(chi.fd, tmp))
			return (-2);
		pid = fork();
		if (pid == 0)
		{
			child_p(&chi, cmd, tmp, data);
			for_path(cmd, data);
		}
		if (for_fork(pid, &chi, tmp))
			data->exit_num = 1;
		tmp = tmp->next;
	}
	return (pid);
}
