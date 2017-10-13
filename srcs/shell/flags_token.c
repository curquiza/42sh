/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 17:31:40 by curquiza          #+#    #+#             */
/*   Updated: 2017/07/10 17:12:43 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_put_token_name(enum e_token token)
{
	ft_putstr("token = ");
	if (token == NEW_LINE)
		ft_putendl("NEWLINE");
	else if (token == WORD)
		ft_putendl("WORD");
	else if (token == ASS_WORD)
		ft_putendl("ASS_WORD");
	else if (token == CTRL_OP)
		ft_putendl("CTRL_OP");
	else if (token == RED_OP)
		ft_putendl("RED_OP");
	else if (token == IO_NBR)
		ft_putendl("IO_NBR");
}

void	ft_put_op_name(enum e_op op)
{
	if (op)
	{
		ft_putstr("op = ");
		op == SEMIC ? ft_putendl("SEMIC") : 0;
		op == DSEMIC ? ft_putendl("DSEMIC") : 0;
		op == PIPE ? ft_putendl("PIPE") : 0;
		op == DPIPE ? ft_putendl("DPIPE") : 0;
		op == AND ? ft_putendl("AND") : 0;
		op == DAND ? ft_putendl("DAND") : 0;
		op == LESS ? ft_putendl("LESS") : 0;
		op == DLESS ? ft_putendl("DLESS") : 0;
		op == GREAT ? ft_putendl("GREAT") : 0;
		op == DGREAT ? ft_putendl("DGREAT") : 0;
		op == LESSAND ? ft_putendl("LESSAND") : 0;
		op == GREATAND ? ft_putendl("GREATAND") : 0;
		op == LESSGREAT ? ft_putendl("LESSGREAT") : 0;
		op == DLESSDASH ? ft_putendl("DLESSDASH") : 0;
		op == CLOBBER ? ft_putendl("CLOBBER") : 0;
	}
}

void	ft_put_lexlst(t_lexeme *lst)
{
	t_lexeme	*current;

	if (lst)
		ft_putendl_col("\n--- TOKENS ---\n", B_YELLOW, DEF);
	current = lst;
	while (current)
	{
		if (current->token == CTRL_OP)
			ft_putendl_col(current->s, RED, DEF);
		else
			ft_putendl(current->s);
		ft_put_token_name(current->token);
		ft_put_op_name(current->op);
		ft_putendl("");
		current = current->next;
	}
	if (lst)
		ft_putendl_col("--------------", B_YELLOW, DEF);
}
