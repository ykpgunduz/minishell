/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 18:06:45 by zkarali           #+#    #+#             */
/*   Updated: 2026/06/02 16:00:23 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	for_read(t_cmd *cmd, int prev_fd, t_ms *data)
{
	int	read;

	read = for_infile(cmd);
	if (read == -1)
	{
		for_err(cmd->infile, NULL, strerror(errno));
		return (-1);
	}
	else if (read == -3)
	{
		for_free(data);
		exit(130);
	}
	if (read > 0)
	{
		dup2(read, STDIN_FILENO);
		close(read);
		if (prev_fd > 0)
			close(prev_fd);
	}
	else
		for_prev(prev_fd);
	return (0);
}

void	in_child_p(t_cmd *cmd, t_chi *chi, t_ms *data, t_list *tmp)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (for_read(cmd, chi->prev_fd, data) == -1)
	{
		if (tmp->next)
		{
			close(chi->fd[1]);
			close(chi->fd[0]);
		}
		if (chi->prev_fd > 0)
			close(chi->prev_fd);
		data->exit_num = 1;
		for_free(data);
		exit(1);
	}
}

static void	for_pipes_exit(pid_t p, t_ms *data)
{
	int		status;
	pid_t	cur;
	int		i;

	i = 0;
	while (1)
	{
		cur = wait(&status);
		if (cur <= 0)
			break ;
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			i = 1;
		if (cur == p)
			for_wait_exit(data, status);
	}
	if (i)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

static void	for_env_builtin(t_cmd *cmd, t_ms *data)
{
	int	fd;
	int	out_fd;

	if (cmd->args[0] && ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (for_exit(cmd, data));
	fd = dup(STDOUT_FILENO);
	out_fd = for_outfile(cmd);
	if (out_fd == -1)
	{
		close(fd);
		for_err(cmd->outfile, NULL, strerror(errno));
		data->exit_num = 1;
		return ;
	}
	dup2(out_fd, STDOUT_FILENO);
	for_builtin(cmd, data);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (out_fd > 1)
		close(out_fd);
}

void	for_execute(t_ms *data)
{
	int		i;
	pid_t	pid;
	t_cmd	*cmd;
	t_list	*tmp;

	i = ft_lstsize(data->cmds);
	cmd = (t_cmd *)data->cmds->content;
	if (i == 1 && is_env_builtin(cmd))
	{
		for_env_builtin(cmd, data);
		return ;
	}
	tmp = data->cmds;
	heredoc(data);
	pid = pipe_loop(data, tmp);
	if (pid == -2)
	{
		for_err("pipe", NULL, strerror(errno));
		data->exit_num = 1;
		return ;
	}
	for_pipes_exit(pid, data);
}
