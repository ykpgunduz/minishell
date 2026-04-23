/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:06:36 by zkarali           #+#    #+#             */
/*   Updated: 2026/03/26 10:01:00 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void handle_redirections(t_cmd *cmd, char **tokens, int *i)//parser
{
    if (ft_strncmp(tokens[*i], "<", 1) == 0 && ft_strlen(tokens[*i]) == 1)
    {
        if (!tokens[*i + 1])
        {
            ft_putendl_fd("syntax error near unexpected token `newline'", 2);
            return ;
        }
        cmd->type_in = REDIR_IN;
        if (cmd->infile)
            free(cmd->infile);
        cmd->infile = ft_strdup(tokens[++(*i)]);
    }
    else if (ft_strncmp(tokens[*i], "<<", 2) == 0 && ft_strlen(tokens[*i]) == 2)
    {
        if (!tokens[*i + 1])
        {
            ft_putendl_fd("syntax error near unexpected token `newline'", 2);
            return ;
        }
        cmd->type_in = HEREDOC;
        if (cmd->delimiter)
            free(cmd->delimiter);
        cmd->delimiter = ft_strdup(tokens[++(*i)]);
        cmd->expand = 1;
    }
    else if (ft_strncmp(tokens[*i], ">", 1) == 0 && ft_strlen(tokens[*i]) == 1)
    {
        if (!tokens[*i + 1])
        {
            ft_putendl_fd("syntax error near unexpected token `newline'", 2);
            return ;
        }
        cmd->type_out = REDIR_OUT;
        if (cmd->outfile)
            free(cmd->outfile);
        cmd->outfile = ft_strdup(tokens[++(*i)]);
    }
    else if (ft_strncmp(tokens[*i], ">>", 2) == 0 && ft_strlen(tokens[*i]) == 2)
    {
        if (!tokens[*i + 1])
        {
            ft_putendl_fd("syntax error near unexpected token `newline'", 2);
            return ;
        }
        cmd->type_out = APPEND;
        if (cmd->outfile)
            free(cmd->outfile);
        cmd->outfile = ft_strdup(tokens[++(*i)]);
    }
}

static t_list *mock_parser(char *line)//parser
{
    t_list  *cmd_list = NULL;
    t_cmd   *new_cmd;
    char    **tokens;
    int     i;
    int     j;

    tokens = ft_split(line, ' '); // strtok yerine 42 usulü split
    i = 0;
    while (tokens[i])
    {
        new_cmd = malloc(sizeof(t_cmd));
        ft_memset(new_cmd, 0, sizeof(t_cmd)); // Önemli: Her şeyi NULL/0 yap
        new_cmd->args = malloc(sizeof(char *) * 64);
        
        j = 0;
        while (tokens[i] && ft_strcmp(tokens[i], "|") != 0)
        {
            if (ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i], "<<") == 0 ||
                ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], ">>") == 0)
			{
                handle_redirections(new_cmd, tokens, &i);
			}
            else
			{
                new_cmd->args[j++] = ft_strdup(tokens[i]);
			}
			i++;
        }
        new_cmd->args[j] = NULL;
        ft_lstadd_back(&cmd_list, ft_lstnew(new_cmd));
        if (tokens[i] && ft_strcmp(tokens[i], "|") == 0) i++;
    }
    free_s(tokens, 2);
    return (cmd_list);
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

static void	for_contents(char **envp, t_env *cont)
{
	char *s;

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

static t_list	*for_the_env(char **envp)
{
	t_list	*enp;
	t_env	*cont;

	enp = NULL;
	while (*envp)
	{
		cont = malloc(sizeof(t_env));
		if (!cont)
			return (NULL);// freeleri fln
		if (ft_strncmp(*envp, "OLDPWD", 6) == 0)
        {
			free(cont);
            envp++;
            continue ;
        }
		for_contents(envp, cont);
		ft_lstadd_back(&enp, ft_lstnew(cont));
		envp++;
	}
	return (enp);
}

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

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_list	*enp;
	t_list	*cmds;

	(void)argc;
	(void)argv;
	cmds = NULL;
	enp = for_the_env(envp);
	while (1)
	{
		line = readline("minishell> ");
		if (!line) // Ctrl+D (EOF) durumunda NULL döner
			break ;
		if (*line && *line != '\n')
		{
			add_history(line);
			cmds = mock_parser(line);
			for_execute(cmds, &enp, line);
			ft_lstclear(&cmds, free_cmd_content);
		}
		free(line);
	}
	ft_lstclear(&enp, for_cont_free);
	rl_clear_history();
	return (0);
}
