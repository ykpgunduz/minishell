/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::  */
/*   free.c                                               :+:      :+:    :+  */
/*                                                      +:+ +:+         +:+   */
/*   By: zkarali <zkarali@student.42istanbul.com.tr>  +#+  +:+       +#+      */
/*                                                  +#+#+#+#+#+   +#+         */
/*   Created: 2026/04/10 07:32:38 by zkarali             #+#    #+#           */
/*   Updated: 2026/04/12 03:50:01 by zkarali            ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	for_cont_free(void *cont)
{
	t_env	*env;

	env = (t_env *)cont;
	if (!env)
		return ;
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	free(env);
}

void	free_cmd_content(void *content)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *)content;
	if (!cmd)
		return ;
	i = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
	}
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outfile)
		free(cmd->outfile);
	if (cmd->delimiter)
		free(cmd->delimiter);
	free(cmd);
}

void	for_free(t_ms *data)
{
	if (data->heredoc_fd > 0)
		close(data->heredoc_fd);
	if (data->cmds)
		ft_lstclear(&data->cmds, free_cmd_content);
	if (data->envp && *(data->envp))
		ft_lstclear(data->envp, for_cont_free);
	if (data->envp)
		free(data->envp);
	if (data->line)
		free(data->line);
	free(data);
	clear_history();
	rl_cleanup_after_signal();
}
