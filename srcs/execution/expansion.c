/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 18:48:16 by curquiza          #+#    #+#             */
/*   Updated: 2017/06/01 12:20:08 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_apply_expansion_on(t_lexeme **lex, t_shell *shell)
{
	t_lexeme	*current;

	current = *lex;
	while (current)
	{
		if (current->token == WORD || current->token == ASS_WORD)
		{
			ft_tilde_expansion(&current->s, shell);
			ft_parameter_expansion(&current->s, shell);
			if (current->hdoc_delim == 0)
				ft_quote_removal(&current->s);
		}
		current = current->next;
	}
}

void	ft_expansion(t_ast *ast)
{
	if (ast)
	{
		ft_apply_expansion_on(&ast->ass_word, ast->shell);
		ft_apply_expansion_on(&ast->cmd, ast->shell);
		ft_apply_expansion_on(&ast->lex, ast->shell);
		ft_apply_expansion_on(&ast->redir, ast->shell);
	}
}
