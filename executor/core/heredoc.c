/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::  */
/*   heredoc.c                                            :+:      :+:    :+  */
/*                                                      +:+ +:+         +:+   */
/*   By: zkarali <zkarali@student.42istanbul.com.tr>  +#+  +:+       +#+      */
/*                                                  +#+#+#+#+#+   +#+         */
/*   Created: 2026/04/10 21:46:17 by zkarali             #+#    #+#           */
/*   Updated: 2026/04/18 02:43:38 by zkarali            ###   ########.fr     */
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

static void	for_h_loop(t_cmd *cmd, t_list *envp, int *fd, t_ms *data)
{
	char	*h_read;

	while (1)
	{
		if (isatty(STDIN_FILENO))
            ft_putstr_fd("> ", STDOUT_FILENO);
        
        // get_next_line satırı sonunda \n ile döner
        h_read = get_next_line(STDIN_FILENO);
        
        if (g_sig == SIGINT || !h_read)
        {
            if (!h_read && g_sig != SIGINT)
                h_msg(cmd);
            free(h_read);
            break ;
        }

        // gnl sonunda \n bıraktığı için delimiter kontrolünden önce onu temizlemeliyiz
        if (h_read[ft_strlen(h_read) - 1] == '\n')
            h_read[ft_strlen(h_read) - 1] = '\0';
		if (ft_strcmp(h_read, cmd->delimiter) == 0)
			return (free(h_read));
		if (cmd->expand)
			h_read = for_expander(h_read, envp, data);
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
	signals_inter();
	if (WIFSIGNALED(s) && WTERMSIG(s) == SIGINT)
	{
		close(fd[0]);
		write(1, "\n", 1);
		g_sig = SIGINT;
		return (-3);
	}
	return (0);
}

int	for_heredoc(t_cmd *cmd, t_list *envp, t_ms *data)
{
	int		fd[2];
	pid_t	p;
	int		i;

	if (pipe(fd) == -1)
		return (-1);
	p = fork();
	if (p == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(fd[0]);
		for_h_loop(cmd, envp, fd, data);
		close(fd[1]);
		for_free(data);
		exit(0);
	}
	i = for_h_parent(p, fd);
	if (i != 0)
		return (i);
	cmd->heredoc_fd = fd[0];
	return (fd[0]);
}
