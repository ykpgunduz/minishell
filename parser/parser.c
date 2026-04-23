#include "parser.h"

int	dispatch_redirect(t_cmd *cmd, char **tokens, int *i)
{
	char	*t;

	t = tokens[*i];
	if (ft_strncmp(t, "<", 1) == 0 && ft_strlen(t) == 1)
		return (handle_input_redirect(cmd, tokens, i));
	if (ft_strncmp(t, "<<", 2) == 0 && ft_strlen(t) == 2)
		return (handle_heredoc(cmd, tokens, i));
	if (ft_strncmp(t, ">>", 2) == 0 && ft_strlen(t) == 2)
		return (handle_append(cmd, tokens, i));
	if (ft_strncmp(t, ">", 1) == 0 && ft_strlen(t) == 1)
		return (handle_output_redirect(cmd, tokens, i));
	return (0);
}

static int	parse_command(t_cmd *cmd, char **tokens, int *i)
{
	int	arg_count;
	int	status;

	arg_count = 0;
	while (tokens[*i] && !is_pipe(tokens[*i]))
	{
		if (is_redirect(tokens[*i]))
		{
			status = dispatch_redirect(cmd, tokens, i);
			if (status < 0)
				return (-1);
		}
		else
		{
			if (add_command_arg(cmd, tokens[*i], &arg_count) < 0)
				return (-1);
			(*i)++;
		}
	}
	cmd->args[arg_count] = NULL;
	return (arg_count > 0);
}

static int	proc_cmd(t_cmd *cmd, char **tokens, int *i, t_list **c_list)
{
	int	status;

	status = parse_command(cmd, tokens, i);
	if (status < 0)
	{
		free(cmd->args);
		free(cmd);
		ft_lstclear(c_list, free_cmd_content);
		return (0);
	}
	if (status > 0)
		ft_lstadd_back(c_list, ft_lstnew(cmd));
	else
	{
		free(cmd->args);
		free(cmd);
	}
	return (1);
}

static t_list	*loop_tokens(char **tokens)
{
	t_list	*cmd_list;
	t_cmd	*cmd;
	int		i;

	cmd_list = NULL;
	i = 0;
	while (tokens[i])
	{
		cmd = create_cmd();
		if (!cmd)
			return (NULL);
		if (!proc_cmd(cmd, tokens, &i, &cmd_list))
			return (NULL);
		if (tokens[i] && is_pipe(tokens[i]))
			i++;
	}
	return (cmd_list);
}

t_list	*parse_input_with_exit(char *input, t_list *envp, int exit_code)
{
	char	**tokens;
	t_list	*cmd_list;

	(void)envp;
	(void)exit_code;
	if (!input || !*input)
		return (NULL);
	tokens = tokenize(input);
	if (!tokens)
		return (NULL);
	if (!validate_syntax(tokens))
	{
		free_tokens(tokens);
		return (NULL);
	}
	cmd_list = loop_tokens(tokens);
	free_tokens(tokens);
	return (cmd_list);
}
