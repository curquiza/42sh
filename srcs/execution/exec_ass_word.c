/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ass_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:50:09 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/19 12:46:46 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	ft_add_assword_var(char *assword, t_shell *shell, int mode)
{
	char		*varname;
	int			i;

	if (!assword)
		return ;
	i = 0;
	while (assword[i] && assword[i] != '=')
		i++;
	varname = ft_strsub(assword, 0, i);
	if (ft_exist_in(shell->var_priv, varname) == 1)
	{
		(mode == 1) ? ft_put_readonly_errmsg(shell->name, NULL, varname) : 0;
		ft_strdel(&varname);
		return;
	}
	else if (mode == 0)
	{
		if (ft_exist_in(shell->var_env, varname) == 1)
			ft_chg_varval(shell->var_env, assword, NULL);
		else
			ft_chg_varval_or_add(&shell->var_loc, assword, NULL);
	}
	else if (mode == 1)
		ft_chg_varval_or_add(&shell->var_env, assword, NULL);
	ft_strdel(&varname);
}

void		ft_do_ass_word(t_ast *ast, int mode)
{
	t_lexeme	*current;

	if (ast)
	{
		current = ast->ass_word;
		while (current)
		{
			ft_add_assword_var(current->s, ast->shell, mode);
			current = current->next;
		}
	}
}
