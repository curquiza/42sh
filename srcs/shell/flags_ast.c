/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 17:46:28 by curquiza          #+#    #+#             */
/*   Updated: 2017/10/18 14:06:16 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_padding(int padd)
{
	int	i;

	i = 0;
	while (++i < padd)
		write(1, "\t", 1);
}

void	ft_print_node(t_ast *ast, char *side, int lvl)
{
	t_lexeme *tmp;

	ft_padding(lvl);
	ft_putstr("** ");
	ft_putstr(side);
	ft_putnbr(lvl);
	ft_putendl(" **");
	ft_padding(lvl);
	tmp = ast->lex;
	ft_putstr(B_PINK);
	while (tmp)
	{
		ft_putstr(tmp->s);
		ft_putstr(" ");
		tmp = tmp->next;
	}
	ft_putendl(DEF);
	ft_padding(lvl);
	ft_putendl("************");
}

void	ft_print_ast(t_ast *ast, char *side, int lvl)
{
	if (!ast)
		return ;
	if (ast->left)
		ft_print_ast(ast->left, "left", ++lvl);
	else
		++lvl;
	ft_print_node(ast, side, lvl);
	if (ast->right)
		ft_print_ast(ast->right, "right", lvl--);
	else
		--lvl;
}

void	ft_putast(t_ast *ast)
{
	if (ast)
	{
		ft_putendl_col("\n---- AST -----\n", B_YELLOW, DEF);
		ft_print_ast(ast, "root", 0);
		ft_putendl_col("--------------", B_YELLOW, DEF);
	}
}
