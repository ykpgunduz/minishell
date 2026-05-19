/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::  */
/*   main.c                                               :+:      :+:    :+  */
/*                                                      +:+ +:+         +:+   */
/*   By: zkarali <zkarali@student.42istanbul.com.tr>  +#+  +:+       +#+      */
/*                                                  +#+#+#+#+#+   +#+         */
/*   Created: 2026/04/01 17:36:32 by zkarali             #+#    #+#           */
/*   Updated: 2026/04/18 06:46:30 by zkarali            ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	for_contents(char **envp, t_env *cont)
{
	char	*s;

	s = ft_strchr(*envp, '=');
	if (s)
	{
		cont->key = ft_substr(*envp, 0, s - *envp);
		cont->value = ft_strdup(s + 1);
	}
	else
	{
		cont->key = ft_strdup(*envp);
		cont->value = NULL;
	}
}

static t_list	*for_the_env(char **enp)
{
	t_list	*envp;
	t_env	*cont;

	envp = NULL;
	while (*enp)
	{
		cont = malloc(sizeof(t_env));
		if (!cont)
			return (NULL);
		for_contents(enp, cont);
		ft_lstadd_back(&envp, ft_lstnew(cont));
		enp++;
	}
	return (envp);
}

static void	main_loop(t_ms *data)
{
	char *line_gnl;
	while (1)
	{
		signals_inter();
		//data->line = readline("minishell> ");
		if (isatty(STDIN_FILENO)) // Giriş terminalden mi?
            data->line = readline("minishell> ");
        else
        {
            line_gnl = get_next_line(STDIN_FILENO);
            if (!line_gnl) // Dosya sonu (EOF) kontrolü
                break ;
            data->line = ft_strtrim(line_gnl, "\n"); // \n karakterini temizle
            free(line_gnl);
        }
		if (g_sig == SIGINT)
		{
			data->exit_num = 130;
			g_sig = 0;
		}
		if (!data->line)
			break ;
		if (*data->line && *data->line != '\n')
		{
			add_history(data->line);
			data->cmds = parse_input_with_exit(data->line, data);
			if (data->cmds)
			{
				for_execute(data);
				ft_lstclear(&data->cmds, free_cmd_content);
			}
		}
		free(data->line);
	}
	if (isatty(STDIN_FILENO))
		write(1, "exit\n", 5);
}

int	main(int argc, char **argv, char **enp)
{
	t_ms	*data;
	int		i;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_ms));
	data->envp = malloc(sizeof(t_list *));
	if (!data->envp)
	{
		free(data);
		return (1);
	}
	*(data->envp) = for_the_env(enp);
	data->exit_num = 0;
	data->heredoc_fd = 0;
	data->cmds = NULL;
	data->line = NULL;
	main_loop(data);
	i = data->exit_num;
	ft_lstclear(data->envp, for_cont_free);
	free(data->envp);
	free(data);
	rl_free_line_state();
	rl_cleanup_after_signal();
	rl_clear_history();
	return (i);
}
