/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:56:08 by zkarali           #+#    #+#             */
/*   Updated: 2026/04/07 12:56:09 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	child_p(int *fd, t_cmd *cmd, t_list *tmp, int prev_fd)
{
	int	write;

	for_read(cmd, prev_fd);
	write = for_outfile(cmd);
	if (write == -1)
	{
		perror(cmd->outfile); //doğru mu
		exit(1);
	}
	else if (write > 1)
	{
		dup2(write, STDOUT_FILENO);
		close(write);
	}
	else if (tmp->next)
		dup2(fd[1], STDOUT_FILENO);
	if (tmp->next)
	{
		close(fd[1]);
		close(fd[0]);
	}
}

static void	parent_p(int *fd, int *prev_fd, t_list *tmp)
{
	if (*prev_fd != 0)
		close(*prev_fd);
	if (tmp->next)
	{
		*prev_fd = fd[0];
		close(fd[1]);
	}
	else
		*prev_fd = 0;
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

static void	for_fork(pid_t pid, int *fd, int *prev_fd, t_list *tmp)
{
	if (pid < 0)
		perror("Fork");
	else if (pid > 0)
		parent_p(fd, prev_fd, tmp);
}

pid_t	pipe_loop(t_list *cmds, t_list **envp, char *line, t_list *tmp)
{
	int		fd[2];
	int		prev_fd;
	pid_t	pid;
	t_cmd	*cmd;

	prev_fd = 0;
	while (tmp)
	{
		cmd = (t_cmd *)tmp->content;
		if (cmd->type_in == HEREDOC)
			cmd->heredoc_fd = for_heredoc(cmd, *envp);
		if (for_pipe(fd, tmp))
			return (-2);
		pid = fork();
		if (pid == 0)
		{
			child_p(fd, cmd, tmp, prev_fd);
			for_path(cmds, cmd, envp, line);
		}
		for_fork(pid, fd, &prev_fd, tmp);
		tmp = tmp->next;
	}
	return (pid);
}
