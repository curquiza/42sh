/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 11:18:45 by curquiza          #+#    #+#             */
/*   Updated: 2017/07/10 17:21:04 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** ft_check_c_op :
** Identifie si le maillon de type t_lexeme est un opérateur de contrôle et, si
** oui, remplit les champs du maillon correspondants.
*/

void	ft_check_c_op(t_lexeme *lex)
{
	if (lex->token != 0)
		return ;
	lex->token = CTRL_OP;
	if (ft_strcmp(lex->s, ";") == 0)
		lex->op = SEMIC;
	else if (ft_strcmp(lex->s, "|") == 0)
		lex->op = PIPE;
	else if (ft_strcmp(lex->s, ";;") == 0)
		lex->op = DSEMIC;
	else if (ft_strcmp(lex->s, "||") == 0)
		lex->op = DPIPE;
	else if (ft_strcmp(lex->s, "&") == 0)
		lex->op = AND;
	else if (ft_strcmp(lex->s, "&&") == 0)
		lex->op = DAND;
	else
		lex->token = 0;
}

/*
** ft_check_r_op :
** Identifie si le maillon de type t_lexeme est un opérateur de redirection et,
** si oui, remplit les champs du maillon correspondants.
*/

void	ft_check_r_op(t_lexeme *lex)
{
	if (lex->token != 0)
		return ;
	lex->token = RED_OP;
	if (!ft_strcmp(lex->s, "<<-"))
		lex->op = DLESSDASH;
	else if (!ft_strcmp(lex->s, "<<"))
		lex->op = DLESS;
	else if (!ft_strcmp(lex->s, ">>"))
		lex->op = DGREAT;
	else if (!ft_strcmp(lex->s, ">&"))
		lex->op = GREATAND;
	else if (!ft_strcmp(lex->s, "<&"))
		lex->op = LESSAND;
	else if (!ft_strcmp(lex->s, "<>"))
		lex->op = LESSGREAT;
	else if (!ft_strcmp(lex->s, ">|"))
		lex->op = CLOBBER;
	else if (!ft_strcmp(lex->s, "<"))
		lex->op = LESS;
	else if (!ft_strcmp(lex->s, ">"))
		lex->op = GREAT;
	else
		lex->token = 0;
}

/*
** ft_check_ass_word :
** Identifie si le maillon de type t_lexeme est un assigment word et, si oui,
** remplit le champ du maillon correspondant.
*/

void	ft_check_ass_word(t_lexeme *lex)
{
	int		i;

	if (lex->token != 0 || !ft_strchr(lex->s, '='))
		return ;
	i = 0;
	if (ft_isdigit(lex->s[i]))
		return ;
	while (lex->s[i] && lex->s[i] != '=')
	{
		if (lex->s[i] != '_' && ft_isalnum(lex->s[i]) == 0)
			return ;
		i++;
	}
	lex->token = ASS_WORD;
}

/*
** ft_token_type :
** Donne un type au token du maillon de type t_lexeme.
*/

void	ft_token_type(t_lexeme *lex, int ind_ionbr, int *ind_assword)
{
	if (ind_ionbr != 0)
		lex->token = IO_NBR;
	if (*lex->s == '\n')
	{
		lex->token = NEW_LINE;
		ft_strdel(&lex->s);
		lex->s = ft_strdup("newline");
	}
	lex->op = 0;
	ft_check_c_op(lex);
	ft_check_r_op(lex);
	if (*ind_assword == 0)
	{
		ft_check_ass_word(lex);
		if (lex->token != ASS_WORD)
			*ind_assword = 1;
	}
	if (lex->token == CTRL_OP)
		*ind_assword = 0;
}
