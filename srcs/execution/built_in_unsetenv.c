/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unsetenv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:49:06 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:49:08 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_builtin_unsetenv(t_ast *ast)
{
	int		i;

	if (ast->argtab && !ast->argtab[1])
	{
		ft_put_errmsg(ast->shell->name, ast->argtab[0], "too few arguments");
		return (CMD_FAILURE);
	}
	i = 1;
	while (ast->argtab && ast->argtab[i])
	{
		ft_suppr_var(&ast->shell->var_env, ast->argtab[i]);
		i++;
	}
	return (CMD_SUCCESS);
}
