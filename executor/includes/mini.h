/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::  */
/*   mini.h                                               :+:      :+:    :+  */
/*                                                      +:+ +:+         +:+   */
/*   By: zkarali <zkarali@student.42istanbul.com.tr>  +#+  +:+       +#+      */
/*                                                  +#+#+#+#+#+   +#+         */
/*   Created: 2026/03/27 20:00:17 by zkarali             #+#    #+#           */
/*   Updated: 2026/04/11 08:56:14 by zkarali            ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include "../types_etc.h"
# include "../parser/includes/parser.h"
# include "builtin/builtin.h"
# include "../get_next_line/get_next_line.h"

extern volatile sig_atomic_t	g_sig;

typedef struct s_chi
{
	int							prev_fd;
	int							fd[2];
}								t_chi;

int			main(int argc, char **argv, char **envp);
void		for_execute(t_ms *data);
char		*fir_check(char **com, t_ms *data);
char		*check_path(char *command, t_ms *data);
void		for_cont_free(void *cont);
void		for_free(t_ms *data);
void		for_path(t_cmd *cmd, t_ms *data);
void		for_check_stat(char *path, t_ms *data);
pid_t		pipe_loop(t_ms *data, t_list *tmp);
int			for_infile(t_cmd *cmd);
int			for_outfile(t_cmd *cmd);
int			for_heredoc(t_cmd *cmd, t_list *envp,
				t_ms *data);
void		for_enoexec(t_cmd *cmd, char *path, char **env,
				t_ms *data);
void		before_path(t_cmd *cmd, t_ms *data);
void		signals_inter(void);
void		for_sigint(int sig);
void		in_child_p(t_cmd *cmd, t_chi *chi, t_ms *data, t_list *tmp);
char		*making_str(char *paths, char *command);
void		heredoc(t_ms *data);

#endif