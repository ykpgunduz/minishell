/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:06:45 by zkarali           #+#    #+#             */
/*   Updated: 2026/04/07 14:36:31 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	for_read(t_cmd *cmd, int prev_fd)
{
	int	read;

	read = for_infile(cmd);
	if (read == -1)
	{
		perror(cmd->infile);
		exit(1);
	}
	else if (read > 0)
	{
		dup2(read, STDIN_FILENO);
		close(read);
	}
	else if (prev_fd > 0)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
}

static int	for_pipes_exit(pid_t p)
{
	int		last_s;
	int		status;
	pid_t	cur;

	last_s = 0;
	while (1)
	{
		cur = wait(&status);
		if (cur <= 0)
			break ;
		if (cur == p)
		{
			if (WIFEXITED(status))
				last_s = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_s = 128 + WTERMSIG(status); //sinyaller bittiyse ctrl c
		}
	}
	return (last_s); //$? için kullanılacak
}

static void	for_env_builtin(t_cmd *cmd, t_list **envp, char *line, t_list *cmds)
{
	int	fd;
	int	out_fd;

	fd = dup(STDOUT_FILENO);
	out_fd = for_outfile(cmd);
	if (out_fd == -1)
	{
		close(fd);
		return (perror("outfile"));
	}
	dup2(out_fd, STDOUT_FILENO);
	builtin_execute(cmd, envp, line, cmds);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (out_fd > 1)
		close(out_fd);
}

void	for_execute(t_list *cmds, t_list **envp, char *line)
{
	int		i;
	pid_t	pid;
	t_cmd	*cmd;
	t_list	*tmp;

	i = ft_lstsize(cmds);
	cmd = (t_cmd *)cmds->content;
	if (i == 1 && is_env_builtin(cmd))
	{
		for_env_builtin(cmd, envp, line, cmds);
		return ;
	}
	tmp = cmds;
	pid = pipe_loop(cmds, envp, line, tmp);
	if (pid == -2)
		return ;
	for_pipes_exit(pid);//returnu sinyal alacak
}
