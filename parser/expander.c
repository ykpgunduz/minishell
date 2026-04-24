/* ************************************************************************** */
/*                                                                            */
/*                                                           :::      ::::::: */
/*   expander.c                                            :+:      :+:    :+ */
/*                                                       +:+ +:+         +:+  */
/*   By: yagunduz <yagunduz@student.42istanbul.com.tr> +#+  +:+       +#+     */
/*                                                   +#+#+#+#+#+   +#+        */
/*   Created: 2026/03/14 09:25:19 by yagunduz             #+#    #+#          */
/*   Updated: 2026/04/23 12:48:48 by yagunduz            ###   ########.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	init_expand_ctx(t_expand_ctx *ctx, char *s, t_ms *data)
{
	ctx->str = s;
	ctx->data = data;
	ctx->left = NULL;
	ctx->mid = NULL;
	ctx->result = NULL;
	ctx->value = NULL;
}

static char	*build_expansion(t_expand_ctx *ctx, char *find, int len)
{
	if (ctx->data && ctx->data->envp)
		ctx->value = get_env_value(ctx->name, *(ctx->data->envp));
	else
		ctx->value = NULL;
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
		return (expand_variables_with_exit(ctx->result, ctx->data));
	return (ctx->result);
}

char	*expand_variable(char *str, t_ms *data)
{
	char			*find;
	t_expand_ctx	ctx;
	int				len;

	if (data && ft_strchr(str, '$') && ft_strchr(str, '$')[1] == '?')
		return (expand_exit_status(str, data));
	find = ft_strchr(str, '$');
	if (!find || !find[1] || !ft_isalpha(find[1]))
		return (str);
	init_expand_ctx(&ctx, str, data);
	ctx.left = ft_substr(str, 0, find - str);
	if (!ctx.left)
		return (str);
	len = extract_var_name(find + 1, ctx.name);
	return (build_expansion(&ctx, find, len));
}

char	*expand_variables(char *token, t_list *envp)
{
	(void)envp;
	return (expand_variables_with_exit(token, NULL));
}

char	*expand_variables_with_exit(char *tok, t_ms *data)
{
	if (!tok)
		return (NULL);
	return (expand_variable(tok, data));
}
