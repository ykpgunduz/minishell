/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 21:46:17 by zkarali           #+#    #+#             */
/*   Updated: 2026/06/02 14:58:48 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	h_msg(t_cmd *cmd)
{
	ft_putstr_fd("minishell: warning: ", 2);
	ft_putstr_fd("here-document delimited by end-of-file (wanted '", 2);
	ft_putstr_fd(cmd->delimiter, 2);
	ft_putendl_fd("')", 2);
}

static void	for_h_loop(t_cmd *cmd, int *fd, t_ms *data)
{
	char	*h_read;

	while (1)
	{
		h_read = readline("> ");
		if (g_sig == SIGINT)
		{
			free(h_read);
			break ;
		}
		if (!h_read)
		{
			h_msg(cmd);
			break ;
		}
		if (ft_strcmp(h_read, cmd->delimiter) == 0)
			return (free(h_read));
		if (cmd->expand)
			h_read = for_h_expander(h_read, *(data->envp), data);
		if (!h_read)
			break ;
		ft_putendl_fd(h_read, fd[1]);
		free(h_read);
	}
}

static int	for_h_parent(pid_t p, int *fd)
{
	int	s;

	if (p < 0)
	{
		close(fd[1]);
		close(fd[0]);
		return (-1);
	}
	close(fd[1]);
	waitpid(p, &s, 0);
	if (WIFSIGNALED(s) && WTERMSIG(s) == SIGINT)
	{
		close(fd[0]);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		g_sig = SIGINT;
		return (-3);
	}
	return (0);
}

int	for_heredoc(t_cmd *cmd, t_ms *data)
{
	int		fd[2];
	pid_t	p;
	int		i;

	if (pipe(fd) == -1)
		return (-1);
	signal(SIGINT, SIG_IGN);
	p = fork();
	if (p == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(fd[0]);
		for_h_loop(cmd, fd, data);
		close(fd[1]);
		for_free(data);
		exit(0);
	}
	i = for_h_parent(p, fd);
	signals_inter();
	if (i != 0)
		return (i);
	cmd->heredoc_fd = fd[0];
	return (fd[0]);
}
