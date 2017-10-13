/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:48:21 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:48:22 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_check_name_err(t_shell *shell, char *name, char *cmd)
{
	if (ft_is_valid_name(name) == 0)
	{
		ft_put_invalidname_errmsg(shell->name, cmd, name);
		return (-1);
	}
	if (ft_get_varvalue(shell->var_priv, name))
	{
		ft_put_readonly_errmsg(shell->name, cmd, name);
		return (-1);
	}
	return (0);
}

int		ft_only_name_export(t_shell *shell, char *arg, char *cmd)
{
	int		ind;

	if (ft_check_name_err(shell, arg, cmd) == -1)
		return (1);
	else if ((ind = ft_get_varindex(shell->var_loc, arg)) != -1)
	{
		ft_chg_varval_or_add(&shell->var_env, shell->var_loc[ind], NULL);
		ft_suppr_var(&shell->var_loc, arg);
	}
	return (0);
}

int		ft_val_with_name_export(t_shell *shell, char *arg, char *cmd)
{
	int		j;
	char	*name;

	j = 0;
	while (arg[j] && arg[j] != '=')
		j++;
	name = ft_strsub(arg, 0, j);
	if (ft_check_name_err(shell, name, cmd) == -1)
	{
		ft_strdel(&name);
		return (1);
	}
	else if ((ft_get_varindex(shell->var_loc, name)) != -1)
	{
		ft_chg_varval_or_add(&shell->var_env, name, arg + j + 1);
		ft_suppr_var(&shell->var_loc, name);
	}
	else
		ft_chg_varval_or_add(&shell->var_env, name, arg + j + 1);
	ft_strdel(&name);
	return (0);
}

int		ft_builtin_export(t_ast *ast)
{
	int		i;
	int		ret;

	if (ast->argtab && !ast->argtab[1])
	{
		ft_put_errmsg(ast->shell->name, ast->argtab[0], "too few arguments");
		return (CMD_FAILURE);
	}
	ret = 0;
	i = 1;
	while (ast->argtab && ast->argtab[i])
	{
		if (!ft_strchr(ast->argtab[i], '='))
			ret = ret
				+ ft_only_name_export(ast->shell, ast->argtab[i],
													ast->argtab[0]);
		else if (ft_strchr(ast->argtab[i], '='))
			ret = ret
				+ ft_val_with_name_export(ast->shell, ast->argtab[i],
														ast->argtab[0]);
		i++;
	}
	return (ret > 0 ? CMD_FAILURE : CMD_SUCCESS);
}
