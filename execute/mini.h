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

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_sig;

typedef enum e_type
{
	NONE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
}								t_type;

typedef struct s_cmd
{
	char						**args;
	char						*infile;
	char						*outfile;
	t_type						type_in;
	t_type						type_out;
	char						*delimiter;
	int							expand;
	int							heredoc_fd;
}								t_cmd;

typedef struct s_env
{
	char						*key;
	char						*value;
}								t_env;

typedef struct s_ms
{
	t_list						**envp;
	t_list						*cmds;
	char						*line;
	int							exit_num;
}								t_ms;

typedef struct s_chi
{
	int							prev_fd;
	int							fd[2];
}								t_chi;

int								main(int argc, char **argv, char **envp);
void							for_execute(t_ms *data);
int								ft_strcmp(const char *s1, const char *s2);
char							*fir_check(char **com, t_ms *data);
char							*check_path(char *command, t_ms *data);
void							free_s(char **s);
void							for_cont_free(void *cont);
void							free_cmd_content(void *content);
void							for_free(t_ms *data);
void							for_path(t_cmd *cmd, t_ms *data);
void							for_check_stat(char *path, t_ms *data);
pid_t							pipe_loop(t_ms *data, t_list *tmp);
void							for_read(t_cmd *cmd, int prev_fd, t_ms *data);
int								for_infile(t_cmd *cmd, t_ms *data);
int								for_outfile(t_cmd *cmd);
int								for_heredoc(t_cmd *cmd, t_list *envp,
									t_ms *data);
void							for_enoexec(t_cmd *cmd, char *path, char **env,
									t_ms *data);
void							before_path(t_cmd *cmd, t_ms *data);
void							signals_inter(void);
void							for_sigint(int sig);
void							heredoc_sig(int sig);
void							for_err(char *com, char *msg, char *err);

#endif