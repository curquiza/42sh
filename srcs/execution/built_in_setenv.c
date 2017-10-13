/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_setenv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:49:22 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:49:54 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_is_valid_name(char *s)
{
	if (!s || ft_isdigit(*s) == 1)
		return (0);
	while (*s)
	{
		if (ft_isalnum(*s) == 0 && *s != '_')
			return (0);
		s++;
	}
	return (1);
}

int		ft_check_err_setenv(t_shell *shell, char *arg, char *cmd)
{
	if (ft_get_varvalue(shell->var_priv, arg))
	{
		ft_put_readonly_errmsg(shell->name, cmd, arg);
		return (1);
	}
	if (ft_is_valid_name(arg) != 1)
	{
		ft_put_invalidname_errmsg(shell->name, cmd, arg);
		return (1);
	}
	return (0);
}

int		ft_builtin_setenv(t_ast *ast)
{
	if (ast->argtab && !ast->argtab[1])
		ft_puttab(ast->shell->var_env);
	else if (ast->argtab && ft_tablen(ast->argtab) > 3)
	{
		ft_put_errmsg(ast->shell->name, ast->argtab[0], "too many arguments");
		return (CMD_FAILURE);
	}
	else if (ast->argtab)
	{
		if (ft_check_err_setenv(ast->shell, ast->argtab[1], ast->argtab[0]))
			return (CMD_FAILURE);
		if (ft_get_varvalue(ast->shell->var_loc, ast->argtab[1]))
			ft_suppr_var(&ast->shell->var_loc, ast->argtab[1]);
		if (!ast->argtab[2])
			ft_chg_varval_or_add(&ast->shell->var_env, ast->argtab[1], "");
		else
			ft_chg_varval_or_add(&ast->shell->var_env, ast->argtab[1],
														ast->argtab[2]);
	}
	return (CMD_SUCCESS);
}
