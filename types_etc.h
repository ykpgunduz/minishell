/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_etc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 11:46:53 by zkarali           #+#    #+#             */
/*   Updated: 2026/05/12 11:46:55 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_ETC_H
# define TYPES_ETC_H

# include "../executor/libft/libft.h"
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

typedef enum e_type
{
	NONE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
}				t_type;

typedef struct s_env
{
	char		*key;
	char		*value;
}				t_env;

typedef struct s_cmd
{
	char		**args;
	char		*infile;
	char		*outfile;
	t_type		type_in;
	t_type		type_out;
	char		*delimiter;
	int			expand;
}				t_cmd;

typedef struct s_ms
{
	t_list		**envp;
	t_list		*cmds;
	char		*line;
	int			heredoc_fd;
	int			exit_num;

}				t_ms;

void			free_cmd_content(void *content);
void			for_err(char *com, char *msg, char *err);
int				ft_strcmp(const char *s1, const char *s2);
void			free_s(char **s);
char			*for_expander(char *s, t_list *envp, t_ms *data);
char			*for_env_value(t_list *envp, char *s);

#endif