/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:45:26 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/23 17:55:51 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		**ft_get_utility(char **arg)
{
	int		i;

	if (!arg)
		return (NULL);
	i = 0;
	while (arg[i])
	{
		if (!ft_strchr(arg[i], '='))
			break ;
		i++;
	}
	return (arg + i);
}

static int	ft_exec_utility_env(t_shell *shell, char **arg)
{
	char		*line;
	char		*tmp;
	t_lexeme	*lex;
	t_ast		*ast;
	int			ret;

	line = NULL;
	while (*arg)
	{
		tmp = line;
		line = ft_strjoin3(tmp, " ", *arg);
		ft_strdel(&tmp);
		arg++;
	}
	lex = NULL;
	ft_lexer(&lex, line);
	ft_ast(lex, &ast, shell);
	ret = 0;
	if (!ast)
		ft_lexlstdel(&lex);
	else
		ret = ft_execution(ast);
	ft_del_ast(&ast);
	ft_strdel(&line);
	return (ret);
}

int			ft_builtin_env(t_ast *ast)
{
	char	*flags;
	char	**arg;
	int		flag_error;
	t_shell	*new_shell;
	int		ret;

	flags = ft_get_flags(ast->argtab + 1);
	if ((flag_error = ft_check_illegal_flags(flags, "i")) != 0)
	{
		ft_put_usage("env", flag_error, "i");
		ft_strdel(&flags);
		return (CMD_FAILURE);
	}
	arg = ft_get_arg(ast->argtab + 1, flag_error);
	new_shell = ft_get_new_shell(arg, flags, ast->shell);
	ret = 0;
	arg = ft_get_utility(arg);
	if (arg && !(*arg))
		ft_puttab(new_shell->var_env);
	else
		ret = ft_exec_utility_env(new_shell, arg);
	ft_del_shell(&new_shell);
	ft_strdel(&flags);
	return (ret != 0 ? CMD_FAILURE : CMD_SUCCESS);
}
