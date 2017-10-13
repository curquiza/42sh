/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:48:36 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:48:36 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_apply_flags_set(char *flags, t_shell *shell)
{
	if (ft_strchr(flags, 'A'))
	{
		ft_putendl("----- ENV -----");
		ft_puttab(shell->var_env);
		ft_putendl("---- LOCAL ----");
		ft_puttab(shell->var_loc);
		ft_putendl("--- PRIVATE ---");
		ft_puttab(shell->var_priv);
	}
	else if (ft_strchr(flags, 'e'))
	{
		ft_putendl("--- ENV ---");
		ft_puttab(shell->var_env);
	}
	else if (ft_strchr(flags, 'l'))
	{
		ft_putendl("--- LOCAL ---");
		ft_puttab(shell->var_loc);
	}
	else if (ft_strchr(flags, 'p'))
	{
		ft_putendl("--- PRIVATE ---");
		ft_puttab(shell->var_priv);
	}
}

int		ft_builtin_set(t_ast *ast)
{
	char	*flags;
	int		flag_error;

	flags = ft_get_flags(ast->argtab + 1);
	if ((flag_error = ft_check_illegal_flags(flags, "Aelp")) != 0)
	{
		ft_put_usage("set", flag_error, "Aelp");
		ft_strdel(&flags);
		return (CMD_FAILURE);
	}
	if (!flags[0])
	{
		ft_puttab(ast->shell->var_env);
		ft_puttab(ast->shell->var_loc);
	}
	else
		ft_apply_flags_set(flags, ast->shell);
	ft_strdel(&flags);
	return (CMD_SUCCESS);
}
