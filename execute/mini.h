/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:06:28 by zkarali           #+#    #+#             */
/*   Updated: 2026/04/07 14:33:17 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "builtin/builtin.h"
# include <readline/readline.h>
# include <readline/history.h>

/*typedef enum e_type
{
	NONE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
}	t_type;

typedef struct s_cmd
{
	char	**args;
	char	*infile;
	char	*outfile;
	t_type	type_in;
	t_type	type_out;
	char	*delimiter;
	int		expand;
	int		heredoc_fd;
}	t_cmd;*/

typedef enum e_type
{
	NONE,// Standart (0 veya 1)
	REDIR_IN,// <
	REDIR_OUT,// >
	APPEND,// >>
	HEREDOC// <<
}	t_type;

typedef struct s_cmd
{
	char	**args;
	char	*infile;//NULL değilse infile var
	char	*outfile;//NULL değilse outfile var
	t_type	type_in;// < mı << mı?
	t_type	type_out;// > mü >> mü?
	char	*delimiter;//eğer heredoc değilse NULL
	int		expand;//çift tırnaklıysa 0, değilse 1 genişletilecek
	int		heredoc_fd;
}	t_cmd;

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef struct s_code
{
	int		num;
}	t_code;

int		main(int argc, char **argv, char **envp);
void	for_execute(t_list *cmd, t_list **envp, char *line);
char	*fir_check(char **com, t_list *envp, char *line, t_list *cmds);
char	*check_path(char *command, t_list *envp, char *line, t_list *cmds);
void	free_s(char **s, int n);
void	for_cont_free(void *cont);
void	free_cmd_content(void *content);
void	for_path(t_list *cmds, t_cmd *md, t_list **envp, char *line);
pid_t	pipe_loop(t_list *cmds, t_list **envp, char *line, t_list *tmp);
void	for_read(t_cmd *cmd, int prev_fd);
int		for_infile(t_cmd *cmd);
int		for_outfile(t_cmd *cmd);
int		for_heredoc(t_cmd *cmd, t_list *envp);

#endif