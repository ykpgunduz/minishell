#include "parser.h"

void	free_tokens(char **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

t_list	*parse_input(char *input)
{
	return (parse_input_with_exit(input, NULL, 0));
}

t_list	*parse_input_with_env(char *input, t_list *envp)
{
	return (parse_input_with_exit(input, envp, 0));
}

t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->args = malloc(sizeof(char *) * 512);
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

int	add_command_arg(t_cmd *cmd, char *arg, int *count)
{
	char	*processed;

	processed = process_quotes(arg);
	if (!processed)
		return (-1);
	cmd->args[*count] = processed;
	(*count)++;
	if (*count >= 511)
	{
		ft_putendl_fd("error: too many arguments", 2);
		return (-1);
	}
	return (1);
}
