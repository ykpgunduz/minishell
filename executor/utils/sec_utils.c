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
