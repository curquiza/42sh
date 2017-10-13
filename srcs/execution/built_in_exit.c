/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:44:35 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:44:37 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_is_numeric_str(char *s)
{
	int		i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (ft_isdigit(s[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}

int		ft_builtin_exit(t_ast *ast)
{
	int		ret;

	if (ast && ast->argtab && ast->argtab[1])
	{
		if (ft_tablen(ast->argtab) > 2)
		{
			ft_put_errmsg(ast->shell->name, ast->argtab[0],
											"too many arguments");
			return (CMD_FAILURE);
		}
		if (ft_is_numeric_str(ast->argtab[1]) == 0)
		{
			ft_put_errmsg(ast->shell->name, ast->argtab[0],
											"only numeric argument");
			return (CMD_FAILURE);
		}
		ret = ft_atoi(ast->argtab[1]);
	}
	else
		ret = ft_atoi(ft_get_varvalue(ast->shell->var_priv, "?"));
	ast->shell->exit_status = ret;
	ast->shell->run = 0;
	return (CMD_SUCCESS);
}
