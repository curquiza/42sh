/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 17:46:28 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/29 20:36:16 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_put_lexlst_word(t_lexeme *lst)
{
	if (!lst)
		ft_putendl("NULL");
	while (lst)
	{
		ft_putendl(lst->s);
		lst = lst->next;
	}
}

void	ft_run_display_ast(t_ast *ast, int step, int move)
{
	step++;
	if (ast->left)
		ft_run_display_ast(ast->left, step, 1);
	if (move == 1)
		ft_putstr("L - ");
	else if (move == 2)
		ft_putstr("R - ");
	else
		ft_putstr("M - ");
	ft_putnbr_endl(step);
	ft_put_lexlst_word(ast->lex);
	ft_putendl("");
	if (ast->right)
		ft_run_display_ast(ast->right, step, 2);
}

void	ft_putast(t_ast *ast)
{
	if (ast)
	{
		ft_putendl_col("\n---- AST -----\n", B_YELLOW, DEF);
		ft_run_display_ast(ast, 0, 0);
		ft_putendl_col("--------------", B_YELLOW, DEF);
	}
}
