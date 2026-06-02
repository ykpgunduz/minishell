/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 14:57:31 by zkarali           #+#    #+#             */
/*   Updated: 2026/06/02 14:14:40 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	close_prev(t_list *s, t_list *e)
{
	t_cmd	*c;

	while (s != e)
	{
		c = (t_cmd *)s->content;
		if (c->type_in == HEREDOC && c->heredoc_fd > 0)
			close(c->heredoc_fd);
		s = s->next;
	}
}

void	heredoc(t_ms *data)
{
	t_list	*tmp;
	t_cmd	*cmd;

	tmp = data->cmds;
	while (tmp)
	{
		cmd = (t_cmd *)tmp->content;
		if (cmd->type_in == HEREDOC)
		{
			cmd->heredoc_fd = for_heredoc(cmd, data);
			if (cmd->heredoc_fd == -3)
			{
				close_prev(data->cmds, tmp);
				return ;
			}
		}
		tmp = tmp->next;
	}
}

void	for_prev(int prev_fd)
{
	if (prev_fd != -1 && prev_fd != 0)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
}

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

void	for_wait_exit(t_ms *data, int status)
{
	if (WIFEXITED(status))
		data->exit_num = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		data->exit_num = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		else if (WTERMSIG(status) == SIGSEGV)
			write(2, "Segmentation fault (core dumped)\n", 34);
	}
}
