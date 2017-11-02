/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:38:54 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 16:54:11 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** ft_puterr_unexp_token :
** Affiche le message d'erreur de syntaxe.
*/

void		ft_puterr_unexp_token(char *token, char *shell_name)
{
	if (shell_name)
		ft_putstr_fd(shell_name, 2);
	ft_putstr_fd(": syntax error near unexpected token `", 2);
	if (token)
		ft_putstr_fd(token, 2);
	ft_putendl_fd("\'", 2);
}

/*
** ft_next_token :
** Renvoie l'adresse du maillon correspondant au prochain token (càd en ne
** tenant pas compte des éventuels tokens de type NEW_LINE)
*/

t_lexeme	*ft_next_token(t_lexeme *lex)
{
	lex = lex->next;
	while (lex && lex->token == NEW_LINE)
		lex = lex->next;
	return (lex);
}

/*
** ft_check_tokenerror :
** Check les erreurs de syntax.
** Renvoie une chaine de char correspondant au token responsable de l'erreur de
** syntaxe.
** Renvoie NULL si aucune erreur n'est trouvée.
*/

char		*ft_check_tokenerror(t_lexeme *lex)
{
	t_lexeme	*next_tok;

	if (lex && lex->token == CTRL_OP)
		return (lex->s);
	while (lex)
	{
		if (lex->op == DSEMIC || lex->op == CLOBBER
			|| lex->op == LESSGREAT || lex->op == DLESSDASH)
			return (lex->s);
		if (lex->token == RED_OP && lex->next && lex->next->token != WORD)
			return (lex->next->s);
		if (lex->token == CTRL_OP && (next_tok = ft_next_token(lex))
			&& next_tok->token == CTRL_OP)
			return (next_tok->s);
		lex = lex->next;
	}
	return (NULL);
}
