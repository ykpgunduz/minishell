/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::  */
/*   exec.c                                               :+:      :+:    :+  */
/*                                                      +:+ +:+         +:+   */
/*   By: zkarali <zkarali@student.42istanbul.com.tr>  +#+  +:+       +#+      */
/*                                                  +#+#+#+#+#+   +#+         */
/*   Created: 2026/03/28 18:06:45 by zkarali             #+#    #+#           */
/*   Updated: 2026/04/18 19:51:28 by zkarali            ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include "builtin/builtin.h"

void	for_read(t_cmd *cmd, int prev_fd, t_ms *data)
{
	int	read;

	read = for_infile(cmd, data);
	if (read == -1)
	{
		for_err(cmd->infile, NULL, strerror(errno));
		data->exit_num = 1;
		exit(1);
	}
	else if (read == -3)
	{
		for_free(data);
		exit(130);
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

static void	for_pipes_exit(pid_t p, t_ms *data)
{
	int		status;
	pid_t	cur;

	while (1)
	{
		cur = wait(&status);
		if (cur <= 0)
			break ;
		if (cur == p)
		{
			if (WIFEXITED(status))
				data->exit_num = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				data->exit_num = 128 + WTERMSIG(status);
				if (WTERMSIG(status) == SIGQUIT)
					write(2, "Quit (core dumped)\n", 19);
				else if (WTERMSIG(status) == SIGINT)
					write(2, "\n", 1);
			}
		}
	}
}

static void	for_env_builtin(t_cmd *cmd, t_ms *data)
{
	int	fd;
	int	out_fd;

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
	builtin_execute(cmd, data);
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
	pid = pipe_loop(data, tmp);
	if (pid == -2)
	{
		for_err("pipe", NULL, strerror(errno));
		data->exit_num = 1;
		return ;
	}
	for_pipes_exit(pid, data);
}
