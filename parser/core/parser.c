/* ************************************************************************** */
/*                                                                            */
/*                                                           :::      ::::::: */
/*   parser.c                                              :+:      :+:    :+ */
/*                                                       +:+ +:+         +:+  */
/*   By: yagunduz <yagunduz@student.42istanbul.com.tr> +#+  +:+       +#+     */
/*                                                   +#+#+#+#+#+   +#+        */
/*   Created: 2026/03/14 09:25:19 by yagunduz             #+#    #+#          */
/*   Updated: 2026/04/23 12:48:48 by yagunduz            ###   ########.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	dispatch_redirect(t_cmd *cmd, char **tokens, int *i, t_ms *data)
{
	char	*t;

	t = tokens[*i];
	if (ft_strncmp(t, "<", 1) == 0 && ft_strlen(t) == 1)
		return (handle_input_redirect(cmd, tokens, i, data));
	if (ft_strncmp(t, "<<", 2) == 0 && ft_strlen(t) == 2)
		return (handle_heredoc(cmd, tokens, i, data));
	if (ft_strncmp(t, ">>", 2) == 0 && ft_strlen(t) == 2)
		return (handle_append(cmd, tokens, i, data));
	if (ft_strncmp(t, ">", 1) == 0 && ft_strlen(t) == 1)
		return (handle_output_redirect(cmd, tokens, i, data));
	return (0);
}

static int	parse_command(t_cmd *cmd, char **tokens, int *i, t_ms *data)
{
	int	arg_count;
	int	status;

	arg_count = 0;
	while (tokens[*i] && !is_pipe(tokens[*i]))
	{
		if (is_redirect(tokens[*i]))
		{
			status = dispatch_redirect(cmd, tokens, i, data);
			if (status < 0)
				return (-1);
		}
		else
		{
			if (add_command_arg(cmd, tokens[*i], &arg_count, data) < 0)
				return (-1);
			(*i)++;
		}
	}
	cmd->args[arg_count] = NULL;
	return (arg_count > 0 || cmd->type_in != NONE
		|| cmd->type_out != NONE);
}

static int	proc_cmd(t_cmd *cmd, char **tokens, int *i, t_ms *data)
{
	int	status;

	status = parse_command(cmd, tokens, i, data);
	if (status < 0)
	{
		data->exit_num = 1;
		return (-1);
	}
	if (status == 0)
	{
		free_cmd_content(cmd);
		return (0);
	}
	return (1);
}

static t_list	*loop_tokens(char **tokens, t_ms *data)
{
	t_list	*cmd_list;
	t_cmd	*cmd;
	int		i;
	int		st;

	cmd_list = NULL;
	i = 0;
	while (tokens[i])
	{
		cmd = create_cmd();
		if (!cmd)
			return (NULL);
		st = proc_cmd(cmd, tokens, &i, data);
		if (st < 0)
		{
			data->exit_num = 1;
			while (tokens[i] && !is_pipe(tokens[i]))
				i++;
		}
		if (st != 0)
			ft_lstadd_back(&cmd_list, ft_lstnew(cmd));
		if (tokens[i] && is_pipe(tokens[i]))
			i++;
	}
	return (cmd_list);
}

t_list	*parse_input_with_exit(char *input, t_ms *data)
{
	char	**tokens;
	t_list	*cmd_list;

	if (!input || !*input)
		return (NULL);
	tokens = tokenize(input);
	if (!tokens)
		return (NULL);
	if (!validate_syntax(tokens))
	{
		data->exit_num = 2;
		free_tokens(tokens);
		return (NULL);
	}
	cmd_list = loop_tokens(tokens, data);
	free_tokens(tokens);
	return (cmd_list);
}
