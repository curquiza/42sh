/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantics.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 20:44:04 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/29 12:35:58 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_semantic_analysis(t_ast *ast)
{
	if (ast)
	{
		if (ast->lex && ast->lex->token != CTRL_OP)
		{
			ft_get_ass_word(ast);
			ft_get_redir(ast);
			ft_get_cmd(ast);
		}
	}
}
