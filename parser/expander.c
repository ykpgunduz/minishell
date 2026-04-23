#include "parser.h"

static void	init_expand_ctx(t_expand_ctx *ctx, char *s, t_list *e, int code)
{
	ctx->str = s;
	ctx->envp = e;
	ctx->last_exit_code = code;
	ctx->left = NULL;
	ctx->mid = NULL;
	ctx->result = NULL;
	ctx->value = NULL;
}

static char	*build_expansion(t_expand_ctx *ctx, char *find, int len)
{
	ctx->value = get_env_value(ctx->name, ctx->envp);
	if (!ctx->value)
		ctx->mid = ft_strdup("");
	else
		ctx->mid = ft_strdup(ctx->value);
	if (!ctx->mid)
	{
		free(ctx->left);
		return (ctx->str);
	}
	ctx->result = expand_part(ctx->left, ctx->mid, ft_strdup(find + 1 + len));
	free(ctx->left);
	free(ctx->mid);
	free(ctx->str);
	if (ft_strchr(ctx->result, '$'))
		return (expand_variables_with_exit(ctx->result, ctx->envp,
				ctx->last_exit_code));
	return (ctx->result);
}

char	*expand_variable(char *str, t_list *envp, int last_exit_code)
{
	char			*find;
	t_expand_ctx	ctx;
	int				len;

	if (ft_strchr(str, '$') && ft_strchr(str, '$')[1] == '?')
		return (expand_exit_status(str, last_exit_code));
	find = ft_strchr(str, '$');
	if (!find || !find[1] || !ft_isalpha(find[1]))
		return (str);
	init_expand_ctx(&ctx, str, envp, last_exit_code);
	ctx.left = ft_substr(str, 0, find - str);
	if (!ctx.left)
		return (str);
	len = extract_var_name(find + 1, ctx.name);
	return (build_expansion(&ctx, find, len));
}

char	*expand_variables(char *token, t_list *envp)
{
	return (expand_variables_with_exit(token, envp, 0));
}

char	*expand_variables_with_exit(char *tok, t_list *envp, int last_exit_code)
{
	if (!tok)
		return (NULL);
	return (expand_variable(tok, envp, last_exit_code));
}
